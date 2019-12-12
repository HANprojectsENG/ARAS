#ifndef COLOR_HPP
#define COLOR_HPP

#include <map>

enum class Color {
    ORANGE = 106,
    GREEN = 37,
    YELLOW = 24,
    BLUE = 23,
    RED = 21
};

const std::map<Color, std::string> COLOR_NAMES = {
    { Color::ORANGE, "Orange" },
    { Color::GREEN, "Green" },
    { Color::YELLOW, "Yellow" },
    { Color::BLUE, "Blue" },
    { Color::RED, "Red" }
};

#endif /* COLOR_HPP */
