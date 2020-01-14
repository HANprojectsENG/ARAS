#ifndef STATESTEP_HPP
#define STATESTEP_HPP

#include <string>

namespace cpparas {

const std::string DEFAULT_SAVED_STEP_PATH = ".cpparas-state";

struct StateStep {
    int layer = -1;
    int step = -1;
    /**
     * @brief Loads a StateStep from the saved step file. If the loading failed, returns the default values for StateStep.
     */
    static StateStep fromFile(const std::string& filePath = DEFAULT_SAVED_STEP_PATH);
    /**
     * @brief Deletes the saved step file.
     */
    static void deleteFile(const std::string& filePath = DEFAULT_SAVED_STEP_PATH);
    /**
     * @brief Saves a StateStep to the saved step file.
     */
    void saveToFile(const std::string& filePath = DEFAULT_SAVED_STEP_PATH);
};

} // namespace cpparas

#endif /* STATESTEP_HPP */
