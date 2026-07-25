#pragma once
#include <fcntl.h>
#include <linux/fb.h>
#include <opencv2/videoio.hpp>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

int getBufferFileDescriptor(const int bufferID);
