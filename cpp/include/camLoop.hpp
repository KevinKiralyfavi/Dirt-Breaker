#include "convert888MatrixTo565Array.hpp"
#include "getBufferFileDescriptor.hpp"
#include "writeFrame.hpp"
#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <thread>

void driveCamLoop(cv::VideoCapture &driveCamera);
void gunCamLoop(cv::VideoCapture &gunCamera);
