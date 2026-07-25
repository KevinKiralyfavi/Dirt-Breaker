#pragma once
#include <cstdint>
#include <fcntl.h>
#include <linux/fb.h>
#include <opencv2/videoio.hpp>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

void writeFrame(const std::array<std::array<uint16_t, 320>, 240> &frame, uint8_t *buffer);
