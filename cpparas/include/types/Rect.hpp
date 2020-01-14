#ifndef RECT_HPP
#define RECT_HPP

#include "types/Point.hpp"

namespace cpparas {

/**
 * @brief A 2-dimensional rectangle with a position and size.
 */
template <typename T>
struct Rect {
    Point<T> origin;
    T width;
    T height;
};

} // namespace cpparas

#endif /* RECT_HPP */
