#include "debug/Debug.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

std::shared_ptr<std::deque<std::string>> Debug::lines;

void Debug::println(const std::string& message)
{
    auto now = std::chrono::high_resolution_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    auto nanosec = now.time_since_epoch();

    std::stringstream ss;
    ss << "[" << std::put_time(std::localtime(&in_time_t), "%X") << "."
       << std::setfill('0') << std::setw(3) << ((nanosec.count() % 1000000000ul) / 1000000ul)
       << "] " << message;
    std::string line = std::string(ss.str());
    std::cout << line << std::endl;

    if (!lines) {
        lines = std::make_shared<std::deque<std::string>>();
    }

    if (lines->size() >= MAX_MEMORY_LOG_LINES) {
        lines->pop_front();
    }
    lines->push_back(line);
}
