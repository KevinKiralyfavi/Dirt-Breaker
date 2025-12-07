// Kevin Kiralyfalvi
// Convert 888 mat to 565 array
// November 28, 2025

#include "convert888MatrixTo565Array.hpp"

std::array<std::array<uint16_t, 320>, 240> convert888MatrixTo565Array(const cv::Mat ARRAY_888)
{
    // Make a blank array where I will place my 16bit integers
    std::array<std::array<uint16_t, 320>, 240> array565;
    // Type Vec3b means that it is a vector that has 3 channels, red, green, and blue, which are in the format RGB888
    cv::Vec3b pixel888;

    // Make all the integers that will store each color value for each color format
    uint8_t r8;
    uint8_t g8;
    uint8_t b8;
    uint16_t r5;
    uint16_t g6;
    uint16_t b5;

    // For each of the columns
    for (int x = 0; x < 320; x++)
    {
        // For each of the rows
        for (int y = 0; y < 240; y++)
        {
            // Save the color information for the designated pixel in format RGB888
            pixel888 = ARRAY_888.at<cv::Vec3b>(y, x);

            // Extract each of the color values
            r8 = pixel888[0];
            g8 = pixel888[1];
            b8 = pixel888[2];

            // In essense, each additional bit only provides more resolution BETWEEN the colors, so cutting them off like this only removes some resolution, which is expected.
            // Cutoff the last 3 bits
            r5 = r8 >> 3;
            // Cutoff the last 2 bits
            g6 = g8 >> 2;
            // Cutoff the last 3 bits
            b5 = b8 >> 3;

            // Squish all of them together and align them correctly
            array565[y][x] = (r5 << 11 | g6 << 5 | b5);
        }
    }

    return array565;
}
