#pragma once

#include "convert888MatrixTo565Array.hpp"
#include "getBufferFileDescriptor.hpp"
#include "writeFrame.hpp"
#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <thread>

void visibleCamLoop(cv::VideoCapture &driveCamera, int bufferID);
