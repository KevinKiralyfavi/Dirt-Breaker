// Kevin Kiralyfalvi
// getVideoDevices
// November 27, 2025

#include "getVideoDevices.hpp"

std::string getVideoDevices()
{
    // Make an array of characters 128 long (cstring)
    std::array<char, 128> buffer{};
    // Make a std::string
    std::string result;

    // FILE doesn't have a constructor, but there are certain functions that return FILE*, so we use those.
    FILE *pipe = popen("v4l2-ctl --list-devices", "r");

    // fgets will return nullptr when there is no more data to read
    // buffer.data() exposes the internal cstring within each std::string
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
        result += buffer.data();

    pclose(pipe);
    return result;
}
