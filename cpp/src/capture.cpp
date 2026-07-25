#include "capture.hpp"

void capture(cv::VideoCapture &cap, cv::Mat &outputFrame, std::mutex &frameMutex, std::condition_variable &frameReady, bool &newFrame)
{
    cv::Mat frame;

    while (true)
    {
        cap >> frame;

        {
            std::lock_guard<std::mutex> lock(frameMutex);
            frame.copyTo(outputFrame);
            newFrame = true;
        }

        // Hey writing thread, check the status of the frame.
        frameReady.notify_one();
    }
}
