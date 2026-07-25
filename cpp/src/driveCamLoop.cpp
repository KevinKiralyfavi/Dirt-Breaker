// Kevin Kiralyfalvi
// Drive Camera Loop
// December 7th, 2025

#include "camLoop.hpp"
#include "convert888MatrixTo565Array.hpp"

void driveCamLoop(cv::VideoCapture &driveCamera)
{
    cv::Mat frame;
    std::array<std::array<uint16_t, 320>, 240> convertedFrame;
    int fb;
    fb_fix_screeninfo finfo;
    uint8_t *buffer;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    std::chrono::milliseconds duration;

    // Get the variable screen info and the fixed screen info
    fb = getBufferFileDescriptor(0);
    ioctl(fb, FBIOGET_FSCREENINFO, &finfo);

    // Get the pointer to the buffer to more easily interact with it in my program
    // 0 means the kernel uses any convenient memory address for mapping
    // smem_len (screen memory length)
    // Protected read and right. Squish them together with bitwise or
    // MAP_SHARED means actually write to the memory instead of a virtual copy
    // fb is the file descriptor from earlier
    // 0 is the offset. Don't offset, and start at the beginning
    buffer = (uint8_t *)mmap(0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
    driveCamera.read(frame);

    /*
    while (true)
    {
        start = std::chrono::high_resolution_clock::now();

        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        convert888MatrixTo565Array(frame, convertedFrame);
        writeFrame(convertedFrame, buffer);
        driveCamera.read(frame);

        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Drive camera took " << duration.count() << " Milliseconds" << std::endl;
    }
    */
}
