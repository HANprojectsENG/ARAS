#ifndef PREFERENCES_HPP
#define PREFERENCES_HPP

#include <string>

namespace cpparas {

const std::string DEFAULT_PREFERENCES_PATH = ".cpparas-preferences";

struct Preferences {
    std::string lastImageFile = "";
    std::string lastSequenceFile = "";
    /**
     * @brief Loads preferences from the saved preferences file. Returns the default values for Preferences if the loading failed.
     */
    static Preferences fromFile(const std::string& filePath = DEFAULT_PREFERENCES_PATH);
    /**
     * @brief Saves preferences to the saved preferences file.
     */
    void saveToFile(const std::string& filePath = DEFAULT_PREFERENCES_PATH);
};

} // namespace cpparas

#endif /* PREFERENCES_HPP */
