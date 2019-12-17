#ifndef MARKERDETECTOR_HPP
#define MARKERDETECTOR_HPP

#include "operators.h"
#include "types/Point2D.hpp"
#include <vector>

namespace MarkerDetector {
std::vector<Point2D> detectMarkers(const image_t* img);
}

#endif /* MARKERDETECTOR_HPP */
