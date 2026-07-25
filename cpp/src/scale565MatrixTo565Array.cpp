// Kevin Kiralyfalvi
// Scale 565 Matrix to 565 Array
// December 7th, 2025

#include "scale565MatrixTo565Array.hpp"

void scale565MatrixTo565Array(cv::Mat const &MATRIX_565, std::array<std::array<uint16_t, 320>, 240> &output)
{
    uint16_t pixel;
    int scaledXIndex;
    int scaledYIndex;

    // For each of the columns
    for (int x = 0; x < 160; x++)
    {
        // For each of the rows
        for (int y = 0; y < 120; y++)
        {
            // Scale a pixel and put it into an array.
            scaledXIndex = x * 2;
            scaledYIndex = y * 2;
            pixel = MATRIX_565.at<uint16_t>(y, x);

            output[scaledYIndex][scaledXIndex] = pixel;
            output[scaledYIndex + 1][scaledXIndex] = pixel;
            output[scaledYIndex][scaledXIndex + 1] = pixel;
            output[scaledYIndex + 1][scaledXIndex + 1] = pixel;
        }
    }
}
