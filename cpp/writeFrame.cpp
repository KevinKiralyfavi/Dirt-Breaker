// Kevin Kiralyfalvi
// writeFrame
// November 27, 2025

#include "writeFrame.hpp"

constexpr int BYTES_ON_SCREEN = 240 * 320 * sizeof(uint16_t);

void writeFrame(const std::array<std::array<uint16_t, 320>, 240> frame, const int bufferID)
{
    // Create the file path to the device
    std::string bufferLocation = std::string("/dev/fb") + std::to_string(bufferID);
    // Open the filestream in binary, deleting anything that was there, and outputting to it
    std::ofstream frameBuffer(bufferLocation, std::ios::binary | std::ios::trunc | std::ios::out);
    // ofstream.write() requires a constant character (array) pointer, so I insist (reinterpret_cast) that my int (array) pointer is actuall a bunch of characters.
    // Because an array int* and an int* are indistinguishable, I have to tell write() how long my array is
    frameBuffer.write(reinterpret_cast<const char *>(frame.data()), BYTES_ON_SCREEN);
}
