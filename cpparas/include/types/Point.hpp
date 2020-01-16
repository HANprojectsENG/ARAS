#ifndef POINT_HPP
#define POINT_HPP

#include <cstdint>
#include <ostream>
#include <sstream>

namespace cpparas {

/**
 * @brief A position in 2-dimensional euclidean space.
 */
template <typename T>
struct Point {
    T col;
    T row;

    Point<T> operator+(const Point<T>& other) const
    {
        return Point<T> {
            col + other.col,
            row + other.row
        };
    }

    Point<T> operator-(const Point<T>& other) const
    {
        return Point<T> {
            col - other.col,
            row - other.row
        };
    }

    bool operator==(const Point<T>& other) const
    {
        return col == other.col
            && row == other.row;
    }

    std::ostream& operator<<(std::ostream& stream) const
    {
        return stream << this->to_string();
    }

    std::string to_string() const
    {
        return std::string("Point(") + std::to_string(col) + std::string(", ") + std::to_string(row) + std::string(")");
    }

    T distanceTo(const Point<T>& other) const
    {
        return sqrt((col - other.col) * (col - other.col) + (row - other.row) * (row - other.row));
    }
};

} // namespace cpparas

#endif /* POINT_HPP */
