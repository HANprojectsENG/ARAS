#ifndef POINT_HPP
#define POINT_HPP

#include <cstdint>

namespace cpparas {

/**
 * @brief A position in 2-dimensional euclidean space.
 */
template <typename T>
struct Point {
    T col;
    T row;
};

} // namespace cpparas

#endif /* POINT_HPP */
