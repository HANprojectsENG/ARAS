#include "StudChecker.hpp"
#include "debug/Debug.hpp"

namespace cpparas {

namespace StudChecker {

    bool matches(const image_t* image, const CoordinateMatrix& coordinateMatrix, const std::vector<Point<uint32_t>> studCoordinates, uint32_t layer, Color expectedColor)
    {
        image_t* hsv_image = newHSVImage((uint32_t)image->cols, (uint32_t)image->rows);
        convertToHSVImage(image, hsv_image);
        //get coordinates in image
        Point<uint32_t> pixelCoordinates;

        image_t* debugImage = newRGB888Image(image->cols, image->rows);
        copy(image, debugImage);

        for (uint32_t i = 0; i < studCoordinates.size(); i++) {
            pixelCoordinates = studCoordinates[i];
            if (!studMatch(hsv_image, coordinateMatrix, pixelCoordinates, layer, expectedColor, debugImage)) {
                Debug::showImage(debugImage);
                deleteImage(debugImage);
                deleteImage(hsv_image);
                return false;
            }
        }
        deleteImage(debugImage);
        deleteImage(hsv_image);
        return true;
    }

    bool studMatch(const image_t* image, const CoordinateMatrix& coordinateMatrix, const Point<uint32_t> studCoordinates, uint32_t layer, Color expectedColor, image_t* debugImage)
    {
        //calculate distance between studs
        int halfDistance = (coordinateMatrix.getMatrix()[layer][0][1].col - coordinateMatrix.getMatrix()[layer][0][0].col) / 2;
        Point<int32_t> pix_coord = coordinateMatrix.getMatrix()[layer][studCoordinates.row][studCoordinates.col];
        int pix_c = pix_coord.col;
        int pix_r = pix_coord.row;

        long int sum_h = 0;
        long int sum_s = 0;
        long int sum_v = 0;
        int num_pixels = 0;
        std::vector<hsv_pixel_t> color_ranges = ColorClassifier::setColors(image, coordinateMatrix, expectedColor);
        hsv_pixel_t max = color_ranges[1];
        hsv_pixel_t min = color_ranges[0];
        hsv_pixel_t pixelHSV;
        hsv_pixel_t average;
        //Calculate average HSV around stud
        for (int r = -halfDistance / 2; r < halfDistance / 2; r++) {
            for (int c = -halfDistance / 2; c < halfDistance / 2; c++) {
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

        //Normal HSV range is from 0-360
        //Red can overlap range and go from 250-10. Needs special case. 
        if(expectedColor == cpparas::Color::RED && min.h < 20){ 
            if (average.h <= min.h && average.h >= max.h) {
                if (average.s >= min.s && average.s <= max.s) {
                    if (average.v >= min.v && average.v <= max.v) {
                        return true;
                    }
                }
            }
        }  
        else if (average.h >= min.h && average.h <= max.h) {
                if (average.s >= min.s && average.s <= max.s) {
                    if (average.v >= min.v && average.v <= max.v) {
                        return true;
                    }
                }
            }
        Debug::println(std::string("Stud color did not match. Stud: ") + studCoordinates.to_string()
            + std::string("\n Average: (H=") + std::to_string(average.h) + std::string(", S=") + std::to_string(average.s) + std::string(", V=") + std::to_string(average.v) + std::string(")")
            + std::string("\n Min threshold: (H=") + std::to_string(min.h) + std::string(", S=") + std::to_string(min.s) + std::string(", V=") + std::to_string(min.v) + std::string(")")
            + std::string("\n Max threshold: (H=") + std::to_string(max.h) + std::string(", S=") + std::to_string(max.s) + std::string(", V=") + std::to_string(max.v) + std::string(")"));

        if (debugImage) {
            int32_t rectTopLeft[2] = { pix_c - halfDistance, pix_r - halfDistance };
            int32_t rectSize[2] = { halfDistance * 2, halfDistance * 2 };
            pixel_t rectColor;
            rectColor.rgb888_pixel = COLOR_DISPLAY_VALUES.at(expectedColor);
            drawRect(debugImage, rectTopLeft, rectSize, rectColor, SHAPE_BORDER, 3);
        }

        return false;
    }

} // namespace StudChecker

} // namespace cpparas
