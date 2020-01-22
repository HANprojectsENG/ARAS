#include "ColorClassifier.hpp"

namespace cpparas {

namespace ColorClassifier {
    std::vector<hsv_pixel_t> setColors(const image_t* image, const CoordinateMatrix& coordinateMatrix, Color expectedColor, image_t* debugImage)
    {
        std::vector<hsv_pixel_t> range;
        int halfDistance = (coordinateMatrix.getMatrix()[0][0][1].col - coordinateMatrix.getMatrix()[0][0][0].col) / 2;
        hsv_pixel_t pixelHSV;
        hsv_pixel_t max = { 0, 0, 0 };
        hsv_pixel_t min = { 360, 100, 100 };
        Point<int32_t> CoordinatesTop = COLOR_COORDINATES_TOP.at(expectedColor);
        Point<int32_t> CoordinatesBottom = COLOR_COORDINATES_BOTTOM.at(expectedColor);
        Point<int32_t> pixelCoordinatesTop = coordinateMatrix.getMatrix()[0][CoordinatesTop.row][CoordinatesTop.col];
        Point<int32_t> pixelCoordinatesBottom = coordinateMatrix.getMatrix()[0][CoordinatesBottom.row][CoordinatesBottom.col];

        if (debugImage) {
            int32_t rectTopLeft[2] = { pixelCoordinatesTop.col - halfDistance, pixelCoordinatesTop.row - halfDistance };
            int32_t rectSize[2] = { halfDistance * 2, halfDistance * 2 };
            pixel_t rectColor;
            rectColor.rgb888_pixel = COLOR_DISPLAY_VALUES.at(expectedColor);
            drawRect(debugImage, rectTopLeft, rectSize, rectColor, SHAPE_INNER, 0);
            rectTopLeft[0] = pixelCoordinatesBottom.col - halfDistance;
            rectTopLeft[1] = pixelCoordinatesBottom.row - halfDistance;
            drawRect(debugImage, rectTopLeft, rectSize, rectColor, SHAPE_INNER, 0);
        }

        for (int r = -halfDistance / 2; r < halfDistance * 2; r++) {
            for (int c = -halfDistance / 2; c < halfDistance * 2; c++) {
                pixelHSV = getHSVPixel(image, c + pixelCoordinatesTop.col, r + pixelCoordinatesTop.row);
                max.h = pixelHSV.h > max.h ? pixelHSV.h : max.h;
                max.s = pixelHSV.s > max.s ? pixelHSV.s : max.s;
                max.v = pixelHSV.v > max.v ? pixelHSV.v : max.v;
                min.h = pixelHSV.h < min.h ? pixelHSV.h : min.h;
                min.s = pixelHSV.s < min.s ? pixelHSV.s : min.s;
                min.v = pixelHSV.v < min.v ? pixelHSV.v : min.v;

                pixelHSV = getHSVPixel(image, c + pixelCoordinatesBottom.col, r + pixelCoordinatesBottom.row);
                max.h = pixelHSV.h > max.h ? pixelHSV.h : max.h;
                max.s = pixelHSV.s > max.s ? pixelHSV.s : max.s;
                max.v = pixelHSV.v > max.v ? pixelHSV.v : max.v;
                min.h = pixelHSV.h < min.h ? pixelHSV.h : min.h;
                min.s = pixelHSV.s < min.s ? pixelHSV.s : min.s;
                min.v = pixelHSV.v < min.v ? pixelHSV.v : min.v;
            }
        }
        //Green has high H value in certain lighting condition, increasing range fixes issue
        if(expectedColor == cpparas::Color::GREEN){ max.h = max.h + 20;}            
        range.push_back(min);
        range.push_back(max);
        return range;
    }
}

} // namespace cpparas
