#include "RegionExtractor.hpp"

RegionExtractor::RegionExtractor(int32_t cols, int32_t rows)
{
    regionImage = newRGB888Image(cols, rows);
    erase(regionImage);
}

RegionExtractor::~RegionExtractor()
{
    deleteImage(regionImage);
}

const image_t* RegionExtractor::getRegionImage() const
{
    return regionImage;
}

bool RegionExtractor::updateImage(const image_t* img)
{
    std::vector<Point2D> corners = MarkerDetector::detectMarkers(img);
    if (corners.size() < 3) {
        return false;
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
        return true;
    }
}
