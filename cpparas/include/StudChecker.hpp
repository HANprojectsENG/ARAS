#ifndef STUDCHECKER_HPP
#define STUDCHECKER_HPP

#include "ColorClassifier.hpp"
#include "CoordinateMatrix.hpp"
#include "operators.h"
#include "types/Color.hpp"

namespace cpparas {

namespace StudChecker {

    /**
     * @brief Checks whether the brick studs in the image match the given color.
     *        If the brick studs don't match, the differences will be printed in the debug log.
     * @param image The cropped image.
     * @param coordinateMatrix The coordinate matrix used to calculate positions.
     * @param studCoordinates The coordinates of the studs of the brick to check.
     * @param layer The layer on which the brick resides.
     * @param expectedColor The expected color.
     */
    bool matches(const image_t* image, const CoordinateMatrix& coordinateMatrix, const std::vector<Point<uint32_t>> studCoordinates, uint32_t layer, Color expectedColor);
    bool studMatch(const image_t* image, const CoordinateMatrix& coordinateMatrix, const Point<uint32_t> studCoordinates, uint32_t layer, Color expectedColor);

}

} // namespace cpparas

#endif /* STUDCHECKER_HPP */
