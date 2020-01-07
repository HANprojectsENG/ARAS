#ifndef STATESTEP_HPP
#define STATESTEP_HPP

#include <string>

namespace cpparas {

const std::string DEFAULT_SAVED_STEP_PATH = ".cpparas-state";

struct StateStep {
    int layer = -1;
    int step = -1;
    static StateStep fromFile(const std::string& filePath = DEFAULT_SAVED_STEP_PATH);
    static void deleteFile(const std::string& filePath = DEFAULT_SAVED_STEP_PATH);
    void saveToFile(const std::string& filePath = DEFAULT_SAVED_STEP_PATH);
};

} // namespace cpparas

#endif /* STATESTEP_HPP */
