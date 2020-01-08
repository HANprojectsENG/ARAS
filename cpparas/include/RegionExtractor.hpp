#ifndef REGIONEXTRACTOR_HPP
#define REGIONEXTRACTOR_HPP

#include "MarkerDetector.hpp"
#include "operators.h"

namespace cpparas {

class RegionExtractor {
public:
    RegionExtractor(int32_t cols, int32_t rows);
    ~RegionExtractor();

    image_t* getRegionImage();
    std::vector<Point<int32_t>> updateImage(const image_t* img);

private:
    image_t* regionImage;
};

} // namespace cpparas

#endif /* REGIONEXTRACTOR_HPP */
