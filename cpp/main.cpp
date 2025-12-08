#include "convert888MatrixTo565Array.hpp"
#include "driveCamLoop.hpp"
#include "getDeviceID.hpp"
#include "getVideoDevices.hpp"
#include "opencv2/imgproc.hpp"
#include "scale565MatrixTo565Array.hpp"
#include "writeFrame.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <thread>

const std::string videoDevices = getVideoDevices();

int main()
{
    cv::VideoCapture cameras[3];
    cv::VideoCapture &driveCamera = cameras[0];
    cv::VideoCapture &gunCamera = cameras[1];
    cv::VideoCapture &thermalCamera = cameras[2];
    cv::Mat frame;

    driveCamera.open(getDeviceID(videoDevices, "046d:0825"), cv::CAP_V4L2);
    driveCamera.set(cv::CAP_PROP_FRAME_HEIGHT, 240);
    driveCamera.set(cv::CAP_PROP_FRAME_HEIGHT, 320);
    driveCamera.set(cv::CAP_PROP_BRIGHTNESS, 64);
    driveCamera.set(cv::CAP_PROP_CONTRAST, 32);
    driveCamera.set(cv::CAP_PROP_SATURATION, 80);
    driveCamera.set(cv::CAP_PROP_GAIN, 0);
    driveCamera.set(cv::CAP_PROP_SHARPNESS, 6);
    driveCamera.set(cv::CAP_PROP_BACKLIGHT, 12);
    // gunCamera.open(getDeviceID(videoDevices, "HD USB Camera"));
    // thermalCamera.open(getDeviceID(videoDevices, "fw:v1.3.0"));

    std::thread driveThread(driveCamLoop, driveCamera);
}
