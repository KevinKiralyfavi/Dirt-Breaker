#pragma once

#include <array>
#include <cstdint>
#include <opencv2/opencv.hpp>

void scale565MatrixTo565Array(cv::Mat const &MATRIX_565, std::array<std::array<uint16_t, 320>, 240> &output);
