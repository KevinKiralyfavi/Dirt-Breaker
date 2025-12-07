#pragma once
#include <cstdint>
#include <fstream>
#include <opencv2/videoio.hpp>
#include <string>

void writeFrame(const std::array<std::array<uint16_t, 320>, 240> frame, const int bufferID);
