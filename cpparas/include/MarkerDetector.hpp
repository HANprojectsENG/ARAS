#ifndef MARKERDETECTOR_HPP
#define MARKERDETECTOR_HPP

#include "operators.h"
#include "types/Point.hpp"
#include <vector>

namespace cpparas {

namespace MarkerDetector {
    /**
     * @brief Detects markers in the given image. Up to three markers can be detected.
     * @return The coordinate of the sharp corner for each marker.
     *         The order is clockwise with the last and first corner having the
     *         greatest difference in angle from the centroid.
     *         In other words: left-top, right-top, right-bottom.
     */
    std::vector<Point<int32_t>> detectMarkers(const image_t* img);
}

} // namespace cpparas

#endif /* MARKERDETECTOR_HPP */
