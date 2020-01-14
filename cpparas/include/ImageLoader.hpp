#ifndef IMAGELOADER_HPP
#define IMAGELOADER_HPP

#include "operators.h"
#include "util/ImageUtils.hpp"
#include <string>

namespace cpparas {

enum class SourceType {
    CAMERA,
    IMAGE,
    UNKNOWN,
};

class ImageLoader {
public:
    /**
     * @brief Creates a new image loader that holds the currently
     *        selected source type and the image seen in the UI.
     */
    ImageLoader();
    ~ImageLoader();
    /**
     * @brief Sets the image source type to be used.
     */
    void Set_source_type(SourceType source);
    SourceType Get_source_type();

    /* TODO: Determine whether these image loading from file functions should be moved elsewhere. */
    /**
     * @brief Sets the source image from an image file.
     */
    void Set_source_image(std::string filePath);
    image_t* Get_source_image();

    /**
     * @brief Sets the frame to be displayed by the UI.
     */
    void Set_UI_frame(image_t* frame);
    image_t* Get_UI_frame();

    /**
     * @brief Returns whether a new UI frame is available.
     */
    bool Get_new_UI_frame_available() const;

private:
    SourceType selected_source;
    image_t* user_image;
    image_t* ui_image;
    bool new_UI_frame_available;
};

} // namespace cpparas

#endif /* IMAGELOADER_HPP */
