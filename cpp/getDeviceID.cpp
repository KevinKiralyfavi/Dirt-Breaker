// Kevin Kiralyfalvi
// findDeviceID
// November 27, 2025

#include "getDeviceID.hpp"

int getDeviceID(std::string videoDevices, std::string code)
{
    int codeIndex;
    int deviceIDIndex;
    int deviceID;

    // Find where the video device's code appears
    codeIndex = videoDevices.find(code);
    // If the code does not appear, return -1
    if (codeIndex == -1)
        return -1;

    // From the beginning of the entry for the specific video device, find the first instance of video (as seen in /dev/video#). From there, add the length of "video" to find the location of the ID. Notably fails when the ID is greater than 9
    deviceIDIndex = videoDevices.find("video", codeIndex) + std::string("video").length();

    // Convert the ascii character number into an integer number because it's offset by 48
    deviceID = ((int)videoDevices[deviceIDIndex]) - 48;
    return deviceID;
}
