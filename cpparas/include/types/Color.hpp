#ifndef COLOR_HPP
#define COLOR_HPP

#include "operators.h"
#include <map>

namespace cpparas {

enum class Color {
    NONE = 0,
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

const std::map<Color, rgb888_pixel_t> COLOR_DISPLAY_VALUES = {
    { Color::ORANGE, { 255, 128, 0 } },
    { Color::GREEN, { 0, 255, 0 } },
    { Color::YELLOW, { 255, 255, 0 } },
    { Color::BLUE, { 0, 0, 255 } },
    { Color::RED, { 255, 0, 0 } }
};

} // namespace cpparas

#endif /* COLOR_HPP */
