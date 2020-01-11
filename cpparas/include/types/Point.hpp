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

template <typename T>
bool operator==(const Point<T>& lhs, const Point<T>& rhs)
{
    return lhs.col == rhs.col
        && lhs.row == rhs.row;
}

} // namespace cpparas

#endif /* POINT_HPP */
