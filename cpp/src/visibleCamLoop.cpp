// Kevin Kiralyfalvi
// Visible Camera Loop
// July 25th, 2026

#include "visibleCamLoop.hpp"
#include "capture.hpp"
#include <mutex>

void visibleCamLoop(cv::VideoCapture &gunCamera, int bufferID)
{
    std::mutex frameMutex;
    cv::Mat rawFrame;
    cv::Mat convertedFrame;
    cv::Mat localFrame;
    int fb;
    fb_fix_screeninfo finfo;
    uint8_t *buffer;
    std::condition_variable frameReady;
    std::unique_lock<std::mutex> lock;
    bool newFrame = false;

    // Get the variable screen info and the fixed screen info
    fb = getBufferFileDescriptor(bufferID);
    ioctl(fb, FBIOGET_FSCREENINFO, &finfo);

    // Get the pointer to the buffer to more easily interact with it in my program
    // 0 means the kernel uses any convenient memory address for mapping
    // smem_len (screen memory length)
    // Protected read and right. Squish them together with bitwise or
    // MAP_SHARED means actually write to the memory instead of a virtual copy
    // fb is the file descriptor from earlier
    // 0 is the offset. Don't offset so start at the beginning
    buffer = (uint8_t *)mmap(0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);

    // Make a thread whose purpose is to grab frames and funnel them into a variable, using mutex to avoid random crashes
    std::thread captureThread(capture, std::ref(gunCamera), std::ref(rawFrame), std::ref(frameMutex), std::ref(frameReady), std::ref(newFrame));

    //Sometimes it can take a little bit to get started, so spin until it reads in the first frame

    while (true)
    {
        //Brackets here to ensure that the lock_guard object destroys itself and unlocks the frame
        {
            //hey buddy capture thread, please don't touch the frame
            std::unique_lock<std::mutex> lock(frameMutex);

            //okay fine you can touch the frame, but tell me when you do
            //when the value in the lambda evaluates to be true, i'll start moving again (AKA, when the capture thread tells me to)
            frameReady.wait(lock, [&] {
                return newFrame;
            });

            //I want to give access to the raw frame back to the capture thread as quickly as possible, so make a copy in order to achieve that.
            rawFrame.copyTo(localFrame);
            // I just ate the new frame. Order up!
            newFrame = false;
        }

        cv::cvtColor(localFrame, convertedFrame, cv::COLOR_BGR2BGR565);
        memcpy(buffer, convertedFrame.data, convertedFrame.total() * sizeof(uint16_t));
    }
}
