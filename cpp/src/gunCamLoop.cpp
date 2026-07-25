// Kevin Kiralyfalvi
// Gun Camera Loop
// December 7th, 2025

#include "camLoop.hpp"
#include "capture.hpp"

void capture(cv::VideoCapture &cap, cv::Mat &outputFrame, std::mutex &frameMutex);

void gunCamLoop(cv::VideoCapture &gunCamera)
{
    std::mutex frameMutex;
    cv::Mat rawFrame;
    cv::Mat convertedFrame;
    int fb;
    fb_fix_screeninfo finfo;
    uint8_t *buffer;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    std::chrono::milliseconds duration;

    // Get the variable screen info and the fixed screen info
    fb = getBufferFileDescriptor(1);
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
    std::thread captureThread(capture, std::ref(gunCamera), std::ref(rawFrame), std::ref(frameMutex));

    //Sometimes it can take a little bit to get started, so spin until it reads in the first frame
    while (rawFrame.empty())
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    while (true)
    {
        //Brackets here to ensure that the lock_guard object destroys itself and unlocks the frame
        {
            std::lock_guard<std::mutex> lock(frameMutex);
            //Who knew that opencv already had a function for this?
            cv::cvtColor(rawFrame, convertedFrame, cv::COLOR_BGR2BGR565);
            memcpy(buffer, convertedFrame.data, convertedFrame.total() * sizeof(uint16_t));
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}
