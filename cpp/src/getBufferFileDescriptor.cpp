// Kevin Kiralyfalvi
// getBufferFileDescriptor
// June 23, 2026

#include "getBufferFileDescriptor.hpp"

int getBufferFileDescriptor(const int bufferID)
{
    std::string bufferPath;
    // File descriptor of the display
    int fb;
    // Struct that holds the unchanging (fixed) information about the display
    // fb_fix_screeninfo finfo;
    // Pointer to the place in memory that I will map the memory to
    // uint8_t *buffer;

    // Assemble the path of the file
    bufferPath = std::string("/dev/fb") + std::to_string(bufferID);

    // Get the file descriptor of the framebuffer.
    fb = open(bufferPath.c_str(), O_RDWR);

    // Get the variable screen info and the fixed screen info

    // ioctl(fb, FBIOGET_FSCREENINFO, &finfo);

    // Get the pointer to the buffer to more easily interact with it in my program
    // 0 means the kernel uses any convenient memory address for mapping
    // smem_len (screen memory length)
    // Protected read and right. Squish them together with bitwise or
    // MAP_SHARED means actually write to the memory instead of a virtual copy
    // fb is the file descriptor from earlier
    // 0 is the offset. Don't offset, and start at the beginning

    // buffer = (uint8_t *)mmap(0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);

    return fb;
}
