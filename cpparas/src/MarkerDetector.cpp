#include "MarkerDetector.hpp"

std::vector<Point2D> MarkerDetector::detectMarkers(const image_t* img)
{
    image_t* dst_thresh = newBasicImage(img->cols, img->rows);
    image_t* src_basic = newRGB888Image(img->cols, img->rows);
    copy(img,src_basic);
    src_basic = toBasicImage(src_basic);
    image_t* dst_scaled = newBasicImage((img->cols)/8, (img->rows)/8);
    image_t* dst_harris = newBasicImage(dst_scaled->cols, dst_scaled->rows);
    image_t* dst_eroded = newBasicImage(img->cols, img->rows);

    threshold(src_basic,dst_thresh,187,255,1);
    invert(dst_thresh,dst_thresh);
    binaryErode(dst_thresh,dst_eroded,8);
    binaryErode(dst_eroded,dst_thresh,8);
    invert(dst_thresh,dst_thresh);
    binaryErode(dst_thresh,dst_eroded,8);
    scaleImage(dst_eroded,dst_scaled);

    Corner(dst_scaled,dst_harris,2,7,0.04,0);
    
    uint16_t c;
    uint16_t r;
    basic_pixel_t pixel;
    uint16_t pos_x[30] = {0};
    uint16_t pos_y[30] = {0};
    uint8_t corners = 0;

    std::vector<Point2D> points;

    for (c = 0; c < dst_harris->cols; c++) {
        for (r = 0; r < dst_harris->rows; r++) {
            pixel = getBasicPixel(dst_harris, c, r);
            if (pixel == 0) {
                pos_x[corners] = c;
                pos_y[corners] = r;
                corners++;
            } 
        }
    }
    Point2D point1;
    Point2D point2;
    Point2D point3;
    if(corners == 3){
        if(pos_x[0] < pos_x[1] && pos_x[0] < pos_x[2]){
            point1.col = pos_x[0];
            point1.row = pos_y[0];
            if (pos_y[1] > pos_y[2]){
                point3.col = pos_x[1];
                point3.row = pos_y[1];
                point2.col = pos_x[2];
                point2.row = pos_y[2];
            }
            else{
                point2.col = pos_x[2];
                point2.row = pos_y[2];
                point3.col = pos_x[1];
                point3.row = pos_y[1];
            }
        }
        else if (pos_x[1] < pos_x[2]){
            point1.col = pos_x[1];
            point1.row = pos_y[1];
            if (pos_y[0] > pos_y[2]){
                point2.col = pos_x[0];
                point2.row = pos_y[0];
                point3.col = pos_x[2];
                point3.row = pos_y[2];
            }
            else{
                point3.col = pos_x[2];
                point3.row = pos_y[2];
                point2.col = pos_x[0];
                point2.row = pos_y[0];
            }
        }
        else{
            point1.col = pos_x[2];
            point1.row = pos_y[2];
            if (pos_y[0] > pos_y[1]){
                point2.col = pos_x[0];
                point2.row = pos_y[0];
                point3.col = pos_x[1];
                point3.row = pos_y[1];
            }
            else{
                point2.col = pos_x[1];
                point2.row = pos_y[1];
                point3.col = pos_x[0];
                point3.row = pos_y[0];
            }
        }
        points.push_back(point1);
        points.push_back(point2);
        points.push_back(point3);
    }
    deleteImage(dst_eroded);
    deleteImage(dst_thresh);
    deleteImage(src_basic);
    deleteImage(dst_scaled);
    deleteImage(dst_harris);
    return points;
}
