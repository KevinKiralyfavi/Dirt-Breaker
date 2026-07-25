#pragma once

#include <mutex>
#include <condition_variable>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

void capture(cv::VideoCapture &cap, cv::Mat &outputFrame, std::mutex &frameMutex, std::condition_variable &frameReady, bool &newFrame);
