#ifndef RECT_HPP
#define RECT_HPP

#include "types/Point.hpp"

namespace cpparas {

template <typename T>
struct Rect {
    Point<T> origin;
    T width;
    T height;
};

} // namespace cpparas

#endif /* RECT_HPP */
