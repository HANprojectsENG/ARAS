#include "MarkerDetector.hpp"

std::vector<Point2D> MarkerDetector::detectMarkers(const image_t* img)
{
    image_t* dst_thresh = newBasicImage(img->cols, img->rows);
    image_t* src_basic = newRGB888Image(img->cols, img->rows);
    copy(img,src_basic);
    src_basic = toBasicImage(src_basic);
    image_t* dst_scaled = newBasicImage((img->cols)/10, (img->rows)/10);
    image_t* dst_harris = newBasicImage(dst_scaled->cols, dst_scaled->rows);

    threshold(src_basic,dst_thresh,210,255,255);
    scaleImage(dst_thresh,dst_scaled);
    //Apply two erode and one dilation?
    //Check for corner, return basic binary image
    //Scan and record locations of corners
    //find three best corners based on distance between
    //If this fails, retry retry another erosion/dilation? 
    //return three corner values

    Corner(dst_scaled,dst_harris,2,7,0.04,0);
    
    
    image_t* dst = toRGB888Image(dst_harris);
    deleteImage(dst_thresh);
    deleteImage(src_basic);
    deleteImage(dst_scaled);
    deleteImage(dst_harris);
    return std::vector<Point2D>();
}
