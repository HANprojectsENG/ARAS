#ifndef COORDINATEMATRIX_HPP
#define COORDINATEMATRIX_HPP

#include "types/Calibration.hpp"
#include "types/Point.hpp"
#include <vector>

namespace cpparas {

typedef std::vector<std::vector<std::vector<Point<int32_t>>>> PointMatrix;

class CoordinateMatrix {
public:
    /**
     * @brief Creates a new uninitialised coordinate matrix.
     */
    CoordinateMatrix(Calibration calibration_);

    /**
     * @brief Calculates the coordinate matrix values.
     *        The input parameters represent cropped camera frame coordinates of the baseplate.
     */
    void update(uint32_t baseplateX, uint32_t baseplateY, uint32_t baseplateWidth, uint32_t baseplateHeight);

    /**
     * @brief Returns the calculated matrix. The values represent cropped camera frame coordinates.
     *        The values can be accessed by matrix[layer][row][column].
     * @note This will return an empty vector when the .update function has not been ran yet.
     */
    const PointMatrix& getMatrix() const;

private:
    PointMatrix matrix;
    Calibration calibration;
};

} // namespace cpparas

#endif /* COORDINATEMATRIX_HPP */
