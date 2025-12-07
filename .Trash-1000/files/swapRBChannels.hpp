#pragma once

#include <array>
#include <cstdint>

std::array<std::array<uint16_t, 320>, 240> swapRBChannels(std::array<std::array<uint16_t, 320>, 240> unswappedFrame);
