#include "MarkerDetector.hpp"
#include "debug/Debug.hpp"
#include <algorithm>  

namespace cpparas {

std::vector<Point<int32_t>> MarkerDetector::detectMarkers(const image_t* img)
{
    std::vector<Point<int32_t>> points;
    uint8_t increment = 5;
    for (uint8_t thresh = 180; thresh < 220; thresh += increment ){
        points = detectPoints(img,thresh);
        if (points.size() == 3){
            printf("thresh:%d\n",thresh);
            return points;
        }
    }
    return points;
}

std::vector<Point<int32_t>> MarkerDetector::detectPoints(const image_t* img, const uint8_t thresh_val){

    image_t* img_basic = newRGB888Image(img->cols, img->rows);
    image_t* src_basic = newBasicImage(img->cols / 2, img->rows / 2);
    copy(img, img_basic);
    img_basic = toBasicImage(img_basic);
    scaleImage(img_basic, src_basic);
    image_t* dst_thresh = newBasicImage(src_basic->cols, src_basic->rows);
    image_t* dst_scaled = newBasicImage((src_basic->cols) / 4, (src_basic->rows) / 4);
    image_t* dst_harris = newBasicImage(dst_scaled->cols, dst_scaled->rows);
    image_t* dst_eroded = newBasicImage(src_basic->cols, src_basic->rows);

    threshold(src_basic, dst_thresh, thresh_val, 255, 1);
    clear_center(dst_thresh);
    invert(dst_thresh, dst_thresh, 1);
    binaryErode(dst_thresh, dst_eroded, 8);
    binaryErode(dst_eroded, dst_thresh, 8);
    invert(dst_thresh, dst_thresh, 1);
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

        //Check distance between points are correct distance
        int distance_x;
        int distance_y;
        double distance_01;
        double distance_12;
        double distance_02;

        distance_x = (point1.col - point0.col) * (point1.col - point0.col);
        distance_y = (point1.row - point0.row) * (point1.row - point0.row);
        distance_01 = sqrt(distance_x + distance_y);

        distance_x = (point2.col - point1.col) * (point2.col - point1.col);
        distance_y = (point2.row - point1.row) * (point2.row - point1.row);
        distance_12 = sqrt(distance_x + distance_y);

        distance_x = (point2.col - point0.col) * (point2.col - point0.col);
        distance_y = (point2.row - point0.row) * (point2.row - point0.row);
        distance_02 = sqrt(distance_x + distance_y);

        if(distance_01 > 500 && distance_01 < 1100 &&
           distance_12 > 500 && distance_12 < 1100 &&
           distance_02 > 700 && distance_02 < 1300){
            points.push_back(point0);
            points.push_back(point1);
            points.push_back(point2);
        }
    }
    deleteImage(dst_eroded);
    deleteImage(dst_thresh);
    deleteImage(src_basic);
    deleteImage(dst_scaled);
    deleteImage(dst_harris);
    return points;
}


} // namespace cpparas
