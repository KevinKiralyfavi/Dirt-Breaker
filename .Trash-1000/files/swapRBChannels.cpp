#include "swapRBChannels.hpp"

std::array<std::array<uint16_t, 320>, 240> swapRBChannels(std::array<std::array<uint16_t, 320>, 240> unswappedFrame)
{
    std::array<std::array<uint16_t, 320>, 240> swappedFrame;
    uint16_t r;
    uint16_t g;
    uint16_t b;
    uint16_t pixel;

    for (int x = 0; x < 320; x++)
    {
        for (int y = 0; y < 240; y++)
        {
            pixel = unswappedFrame[y][x];

            r = pixel & 0b1111100000000000;
            g = pixel & 0b0000011111100000;
            b = pixel & 0b0000000000011111;

            r >>= 11;
            b <<= 11;

            swappedFrame[y][x] = r | g | b;
        }
    }
    return swappedFrame;
}
