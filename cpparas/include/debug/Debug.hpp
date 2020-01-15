#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "operators.h"
#include <deque>
#include <map>
#include <memory>
#include <string>

namespace cpparas {

namespace Debug {
    const uint32_t MAX_MEMORY_LOG_LINES = 200;

    /**
     * @brief Adds a line to the debug log.
     *        Prints the line to the standard output.
     */
    void println(const std::string& line);
    void showImage(const std::string& name, const image_t* image);

    const std::shared_ptr<std::deque<std::string>>& getLines();
    const image_t* getImage();
}

} // namespace cpparas

#endif /* DEBUG_HPP */
