#include "StudChecker.hpp"

namespace cpparas {

namespace StudChecker {

    bool matches(const image_t* image, const CoordinateMatrix& coordinateMatrix, const std::vector<Point<uint32_t>> studCoordinates, Color expectedColor){
    //calculate distance between studs

    int halfDistance = 15;
    Point<uint32_t> pt = coordinateMatrix.getMatrix()[0][0][0];
    long int sum_h = 0;
    long int sum_s = 0;
    long int sum_v = 0;
    int num_pixels = 0;
    hsv_pixel_t pixelHSV;
    hsv_pixel_t average;
    hsv_pixel_t max = {255,255,255};
    hsv_pixel_t min = {0,0,0};
    (void)coordinateMatrix;
    (void)studCoordinates;
    (void)expectedColor;

    //get coordinates in image
    Point<int32_t> pixelCoordinates;
    for(uint32_t i = 0; i < sizeof(studCoordinates); i++){
        
    }
    pixelCoordinates.col = 500;
    pixelCoordinates.row = 500;

    //Calculate average HSV around stud
    for(int r = -halfDistance; r < halfDistance; r++){
        for(int c = -halfDistance; c < halfDistance; c++){
            pixelHSV = getHSVPixel(image, c + pixelCoordinates.col, r + pixelCoordinates.row);
            sum_h = sum_h + pixelHSV.h;
            sum_s = sum_s + pixelHSV.s;
            sum_v = sum_v + pixelHSV.v;
            num_pixels++;
        }
    }
    //divide to get average
    average.h = sum_h / num_pixels;
    average.s = sum_s / num_pixels;
    average.v = sum_v / num_pixels;

    //compare average with expected color
    if(average.h > min.h && average.h < max.h){
        if(average.s > min.s && average.s < max.s){
            if(average.v > min.v && average.v < max.v){
                return true;
            }
        }
    }
    return false;
    }

} // namespace StudChecker

} // namespace cpparas
