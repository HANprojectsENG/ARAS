#include "ImageLoader.hpp"

ImageLoader::ImageLoader()
{
}

ImageLoader::~ImageLoader()
{
}

void ImageLoader::Set_source_type(SourceType source)
{
    switch(source)
    {
        case CAMERA:
            selected_source = CAMERA;
            break;
        case IMAGE:
            selected_source = IMAGE;
            break;
        default:
            selected_source = DUNNO;
            break;
    };
}

SourceType ImageLoader::Get_source_type()
{
    return selected_source;
}

void ImageLoader::Set_source_image(std::string filePath)
{
    if(selected_source == IMAGE){
        user_image = ImageUtils::loadImageFromFile(filePath);
    }
}

image_t* ImageLoader::Get_source_image()
{
    if(selected_source == IMAGE){
        return user_image;
    }
    return nullptr;
}