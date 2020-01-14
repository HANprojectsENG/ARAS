#ifndef STUDCHECKER_HPP
#define STUDCHECKER_HPP

#include "ColorClassifier.hpp"
#include "CoordinateMatrix.hpp"
#include "operators.h"
#include "types/Color.hpp"

namespace cpparas {

namespace StudChecker {

    bool matches(const image_t* image, const CoordinateMatrix& coordinateMatrix, const std::vector<Point<uint32_t>> studCoordinates, uint32_t layer, Color expectedColor);
    bool studMatch(const image_t* image, const CoordinateMatrix& coordinateMatrix, const Point<uint32_t> studCoordinates, uint32_t layer, Color expectedColor);

}

} // namespace cpparas

#endif /* STUDCHECKER_HPP */
