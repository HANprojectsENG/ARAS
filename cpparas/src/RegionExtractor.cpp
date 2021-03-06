#include "RegionExtractor.hpp"

namespace cpparas {

RegionExtractor::RegionExtractor(int32_t cols, int32_t rows)
{
    regionImage = newRGB888Image(cols, rows);
    erase(regionImage);
}

RegionExtractor::~RegionExtractor()
{
    deleteImage(regionImage);
}

image_t* RegionExtractor::getRegionImage()
{
    return regionImage;
}

std::vector<Point<int32_t>> RegionExtractor::updateImage(const image_t* img)
{
    std::vector<Point<int32_t>> corners = MarkerDetector::detectMarkers(img);
    if (corners.size() < 3) {
        return corners;
    } else {
        int32_t colpos[3] = {
            corners[0].col,
            corners[1].col,
            corners[2].col,
        };
        int32_t rowpos[3] = {
            corners[0].row,
            corners[1].row,
            corners[2].row
        };
        warp(img, regionImage, colpos, rowpos);
        return corners;
    }
}

} // namespace cpparas
