#ifndef COLORCLASSIFIER_HPP
#define COLORCLASSIFIER_HPP

#include "types/Color.hpp"
#include "CoordinateMatrix.hpp"
#include "operators.h"

namespace cpparas {

namespace ColorClassifier {
    std::vector<hsv_pixel_t> setColors(const image_t* image, const CoordinateMatrix& coordinateMatrix,Color expectedColor);
}

} // namespace cpparas

#endif /* COLORCLASSIFIER_HPP */
