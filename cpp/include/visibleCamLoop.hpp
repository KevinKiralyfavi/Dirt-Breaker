#pragma once

#include "getBufferFileDescriptor.hpp"
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <thread>
#include <cstdint>
#include <fcntl.h>
#include <linux/fb.h>
#include <opencv2/videoio.hpp>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

void visibleCamLoop(cv::VideoCapture &driveCamera, int bufferID);
