#ifndef COORDINATEMATRIX_HPP
#define COORDINATEMATRIX_HPP

#include "types/Calibration.hpp"
#include "types/Point2D.hpp"
#include <vector>

typedef std::vector<std::vector<std::vector<Point2D>>> PointMatrix;

class CoordinateMatrix {
public:
    CoordinateMatrix(Calibration calibration_);

    void update(uint32_t baseplateX, uint32_t baseplateY, uint32_t baseplateWidth, uint32_t baseplateHeight);
    const PointMatrix& getMatrix();

private:
    PointMatrix matrix;
    Calibration calibration;
};

#endif /* COORDINATEMATRIX_HPP */
