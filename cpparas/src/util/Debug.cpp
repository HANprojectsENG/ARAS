#include "util/Debug.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

void Debug::println(const std::string& line)
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%X");
    std::string datestr = ss.str();

    std::cout << "[" << datestr << "] " << line << std::endl;
}
