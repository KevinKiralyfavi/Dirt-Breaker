#include "capture.hpp"

void capture(cv::VideoCapture &cap, cv::Mat &outputFrame, std::mutex &frameMutex)
{
    cv::Mat frame;

    while (true)
    {
        if (!cap.grab())
            continue;

        cap.retrieve(frame);

        {
            std::lock_guard<std::mutex> lock(frameMutex);
            std::swap(outputFrame, frame);
        }
    }
}
