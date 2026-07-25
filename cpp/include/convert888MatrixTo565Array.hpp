#pragma once
#include <array>
#include <cstdint>
#include <opencv2/videoio.hpp>

void convert888MatrixTo565Array(const cv::Mat &ARRAY_888, std::array<std::array<uint16_t, 320>, 240> &output);
