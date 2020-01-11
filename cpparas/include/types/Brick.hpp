#ifndef BRICK_HPP
#define BRICK_HPP

#include "Color.hpp"

namespace cpparas {

/**
 * @brief A rectangular brick with no positional information.
 */
struct Brick {
    Color color;
    uint32_t width;
    uint32_t height;
};

} // namespace cpparas

#endif /* BRICK_HPP */
