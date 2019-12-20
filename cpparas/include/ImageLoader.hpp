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

private:
    SourceType selected_source;
    image_t* user_image;
};

#endif /* IMAGELOADER_HPP */
