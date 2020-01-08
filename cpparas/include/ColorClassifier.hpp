#ifndef COLORCLASSIFIER_HPP
#define COLORCLASSIFIER_HPP

#include "types/Color.hpp"
#include "CoordinateMatrix.hpp"
#include "operators.h"
#include <map>

namespace cpparas {

namespace ColorClassifier {
    bool setColors(const image_t* image, const CoordinateMatrix& coordinateMatrix);
}

} // namespace cpparas

#endif /* COLORCLASSIFIER_HPP */
