#include "StudChecker.hpp"

namespace cpparas {

namespace StudChecker {

    bool matches(const image_t* image, const CoordinateMatrix& coordinateMatrix, const std::vector<Point<uint32_t>> studCoordinates, uint32_t layer, Color expectedColor)
    {
        image_t* hsv_image = newHSVImage((uint32_t)image->cols, (uint32_t)image->rows);
        convertToHSVImage(image,hsv_image);
        //get coordinates in image
        Point<uint32_t> pixelCoordinates;       
        for (uint32_t i = 0; i < sizeof(studCoordinates); i++) {
            pixelCoordinates = studCoordinates[i];
            if(!studMatch(hsv_image, coordinateMatrix, pixelCoordinates, layer, expectedColor)){
                deleteImage(hsv_image);
                return false;
            }
        }
        deleteImage(hsv_image);
        return true;
    }

    bool studMatch(const image_t* image, const CoordinateMatrix& coordinateMatrix, const Point<uint32_t> studCoordinates, uint32_t layer, Color expectedColor){
        //calculate distance between studs
        int halfDistance = (coordinateMatrix.getMatrix()[layer][0][1].col - coordinateMatrix.getMatrix()[layer][0][0].col) / 2;
        int pix_c = coordinateMatrix.getMatrix()[layer][studCoordinates.col][studCoordinates.row].col;
        int pix_r = coordinateMatrix.getMatrix()[layer][studCoordinates.col][studCoordinates.row].row;

        long int sum_h = 0;
        long int sum_s = 0;
        long int sum_v = 0;
        int num_pixels = 0;
        std::vector<hsv_pixel_t> color_ranges = ColorClassifier::setColors(image,coordinateMatrix,expectedColor);
        hsv_pixel_t max = color_ranges[1];
        hsv_pixel_t min = color_ranges[0];
        hsv_pixel_t pixelHSV;
        hsv_pixel_t average;
        //Calculate average HSV around stud
        for (int r = -halfDistance; r < halfDistance; r++) {
            for (int c = -halfDistance; c < halfDistance; c++) {
                pixelHSV = getHSVPixel(image, c + pix_c, r + pix_r);
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
        if (average.h > min.h && average.h < max.h) {
            if (average.s > min.s && average.s < max.s) {
                if (average.v > min.v && average.v < max.v) {
                    return true;
                }
            }
        }
        return false;
    }

} // namespace StudChecker

} // namespace cpparas
