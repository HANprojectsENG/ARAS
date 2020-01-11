#ifndef REGIONEXTRACTOR_HPP
#define REGIONEXTRACTOR_HPP

#include "MarkerDetector.hpp"
#include "operators.h"

namespace cpparas {

class RegionExtractor {
public:
    /**
     * @brief Creates a new region extractor and creates a blank region image.
     * @param cols The width in pixels of the region image.
     * @param rows The height in pixels of the region image.
     */
    RegionExtractor(int32_t cols, int32_t rows);
    ~RegionExtractor();

    /**
     * @brief Returns the region image.
     */
    image_t* getRegionImage();
    /**
     * @brief Runs the marker detection and crops the input image to the region image.
     * @return The detected marker coordinates.
     */
    std::vector<Point<int32_t>> updateImage(const image_t* img);

private:
    image_t* regionImage;
};

} // namespace cpparas

#endif /* REGIONEXTRACTOR_HPP */
