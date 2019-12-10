#ifndef PREFERENCES_HPP
#define PREFERENCES_HPP

#include <string>

const std::string DEFAULT_PREFERENCES_PATH = ".cpparas-preferences";

struct Preferences {
    std::string lastImageFile = "";
    std::string lastSequenceFile = "";
    static Preferences fromFile(const std::string& filePath = DEFAULT_PREFERENCES_PATH);
    void saveToFile(const std::string& filePath = DEFAULT_PREFERENCES_PATH);
};

#endif /* PREFERENCES_HPP */
