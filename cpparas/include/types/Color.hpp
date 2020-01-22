#ifndef COLOR_HPP
#define COLOR_HPP

#include "Point.hpp"
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

const std::map<Color, Point<int32_t>> COLOR_COORDINATES_BOTTOM = {
    { Color::ORANGE, { 12, 18 } },
    { Color::GREEN, { 12, 20 } },
    { Color::YELLOW, { 12, 22 } },
    { Color::BLUE, { 12, 24 } },
    { Color::RED, { 12, 26 } }
};

const std::map<Color, Point<int32_t>> COLOR_COORDINATES_TOP = {
    { Color::ORANGE, { 34, 26 } },
    { Color::GREEN, { 34, 24 } },
    { Color::YELLOW, { 34, 22 } },
    { Color::BLUE, { 34, 20 } },
    { Color::RED, { 34, 18 } }
};

} // namespace cpparas

#endif /* COLOR_HPP */
