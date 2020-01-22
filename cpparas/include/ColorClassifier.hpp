#ifndef COLORCLASSIFIER_HPP
#define COLORCLASSIFIER_HPP

#include "CoordinateMatrix.hpp"
#include "operators.h"
#include "types/Color.hpp"

namespace cpparas {

namespace ColorClassifier {
    std::vector<hsv_pixel_t> setColors(const image_t* image, const CoordinateMatrix& coordinateMatrix, Color expectedColor, image_t* debugImage = nullptr);
}

} // namespace cpparas

#endif /* COLORCLASSIFIER_HPP */
