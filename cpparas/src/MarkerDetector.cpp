#include "MarkerDetector.hpp"
#include "debug/Debug.hpp"
#include <algorithm>  

namespace cpparas {

std::vector<Point<int32_t>> MarkerDetector::detectMarkers(const image_t* img)
{
    image_t* dst_thresh = newBasicImage(img->cols, img->rows);
    image_t* src_basic = newRGB888Image(img->cols, img->rows);
    copy(img, src_basic);
    src_basic = toBasicImage(src_basic);
    image_t* dst_scaled = newBasicImage((img->cols) / 8, (img->rows) / 8);
    image_t* dst_harris = newBasicImage(dst_scaled->cols, dst_scaled->rows);
    image_t* dst_eroded = newBasicImage(img->cols, img->rows);

    threshold(src_basic, dst_thresh, 226, 255, 1);
    invert(dst_thresh, dst_thresh);
    binaryErode(dst_thresh, dst_eroded, 8);
    binaryErode(dst_eroded, dst_thresh, 8);
    invert(dst_thresh, dst_thresh);
    binaryErode(dst_thresh, dst_eroded, 8);
    scaleImage(dst_eroded, dst_scaled);

    Corner(dst_scaled, dst_harris, 2, 7, 0.04, 0);

    uint16_t c;
    uint16_t r;
    basic_pixel_t pixel;
    std::vector<uint32_t> pos_x;
    std::vector<uint32_t> pos_y;
    uint8_t corners = 0;

    std::vector<Point<int32_t>> points;

    for (c = 0; c < dst_harris->cols; c++) {
        for (r = 0; r < dst_harris->rows; r++) {
            pixel = getBasicPixel(dst_harris, c, r);
            if (pixel == 0) {
                pos_x.push_back(c * 8);
                pos_y.push_back(r * 8);
                corners++;
                //Debug::println(std::string("Corner at (") + std::to_string(c) + std::string(", ") + std::to_string(r) + std::string(")"));
            }
        }
    }
    Point<int32_t> point0;
    Point<int32_t> point1;
    Point<int32_t> point2;
    //sort points by size if we have 3 points
    if (corners == 3) {
        point0.col = pos_x[0];
        point0.row = pos_y[0];
        point1.col = pos_x[1];
        point1.row = pos_y[1];
        point2.col = pos_x[2];
        point2.row = pos_y[2];

        if ((point0.col + point0.row) > (point1.col + point1.row)){ std::swap(point0,point1);}
        if ((point1.col + point1.row) > (point2.col + point2.row)){ std::swap(point1,point2);}
        if ((point0.col + point0.row) > (point1.col + point1.row)){ std::swap(point0,point1);}
        points.push_back(point0);
        points.push_back(point1);
        points.push_back(point2);
    }
    deleteImage(dst_eroded);
    deleteImage(dst_thresh);
    deleteImage(src_basic);
    deleteImage(dst_scaled);
    deleteImage(dst_harris);
    return points;
}

} // namespace cpparas
