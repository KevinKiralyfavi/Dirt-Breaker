#pragma once
#include <mutex>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

void capture(cv::VideoCapture &cap, cv::Mat &outputFrame, std::mutex &frameMutex);
