// Kevin Kiralyfalvi
// Drive Camera Loop
// December 7th, 2025

#include "driveCamLoop.hpp"

int driveCamLoop(cv::VideoCapture driveCamera)
{
    cv::Mat frame;
    while (true)
    {
        if (driveCamera.read(frame))
        {
            cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
            writeFrame(convert888MatrixTo565Array(frame), 0);
        }
        else
            std::cout << "Error! Did not find drive frame!";
    }
}
