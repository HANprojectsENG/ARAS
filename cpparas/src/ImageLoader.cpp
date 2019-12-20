#include "ImageLoader.hpp"

ImageLoader::ImageLoader()
{
}

ImageLoader::~ImageLoader()
{
}

//Set the current source type
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

//Get the current source type
SourceType ImageLoader::Get_source_type()
{
    return selected_source;
}

// Set the current source image if not using camera
void ImageLoader::Set_source_image(std::string filePath)
{
    if(selected_source == IMAGE){
        user_image = ImageUtils::loadImageFromFile(filePath);
    }
}

// Get the current source image if not using camera
image_t* ImageLoader::Get_source_image()
{
    if(selected_source == IMAGE){
        return user_image;
    }
    return nullptr;
}

//Save frame to be displayed to ui, and raise flag for the ui to look for a new frame to show
void ImageLoader::Set_UI_frame(image_t* frame)
{
    ui_image = frame;
    new_UI_frame_available = true;
}

//request back the frame that was saved for the ui, used by the ui itself to get the image
image_t* ImageLoader::Get_UI_frame()
{
    new_UI_frame_available = false;
    return ui_image;
}