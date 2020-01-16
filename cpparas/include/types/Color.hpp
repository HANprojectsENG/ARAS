#ifndef COLOR_HPP
#define COLOR_HPP

#include "operators.h"
#include "Point.hpp"
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
    { Color::ORANGE, { 36, 44 } },
    { Color::GREEN, { 34, 44 } },
    { Color::YELLOW, { 32,44 } },
    { Color::BLUE, { 30, 44 } },
    { Color::RED, {28, 44} }
};

const std::map<Color, Point<int32_t>> COLOR_COORDINATES_TOP = {
    { Color::ORANGE, { 10, 3 } },
    { Color::GREEN, { 12, 3 } },
    { Color::YELLOW, { 14, 3 } },
    { Color::BLUE, { 16, 3 } },
    { Color::RED, {18, 3} }
};

} // namespace cpparas

#endif /* COLOR_HPP */
