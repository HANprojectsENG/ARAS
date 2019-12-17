#ifndef REGIONEXTRACTOR_HPP
#define REGIONEXTRACTOR_HPP

#include "MarkerDetector.hpp"
#include "operators.h"

class RegionExtractor {
public:
    RegionExtractor(int32_t cols, int32_t rows);
    ~RegionExtractor();

    const image_t* getRegionImage() const;
    bool updateImage(const image_t* img);

private:
    image_t* regionImage;
};

#endif /* REGIONEXTRACTOR_HPP */
