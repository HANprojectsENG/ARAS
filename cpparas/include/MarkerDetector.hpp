#ifndef MARKERDETECTOR_HPP
#define MARKERDETECTOR_HPP

#include "operators.h"
#include "types/Point.hpp"
#include <vector>

namespace cpparas {

namespace MarkerDetector {
    std::vector<Point<int32_t>> detectMarkers(const image_t* img);
}

} // namespace cpparas

#endif /* MARKERDETECTOR_HPP */
