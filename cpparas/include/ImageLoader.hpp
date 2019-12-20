#ifndef IMAGELOADER_HPP
#define IMAGELOADER_HPP

#include <string>
#include "util/ImageUtils.hpp"
#include "operators.h"

enum SourceType {
    CAMERA,
    IMAGE,
    DUNNO,
};

class ImageLoader {
public:
    ImageLoader();
    ~ImageLoader();
    void Set_source_type(SourceType source);
    SourceType Get_source_type();
    void Set_source_image(std::string filePath);
    image_t* Get_source_image();
    void Set_UI_frame(image_t* frame);
    image_t* Get_UI_frame();
    bool new_UI_frame_available = false;

private:
    SourceType selected_source;
    image_t* user_image;
    image_t* ui_image;
};

#endif /* IMAGELOADER_HPP */
