#ifndef IMAGEUTILS_HPP
#define IMAGEUTILS_HPP

#include "operators.h"
#include <gdkmm/pixbuf.h>

namespace cpparas {

namespace ImageUtils {

    /**
     * @brief Converts an image_t to a Gdk::Pixbuf.
     */
    Glib::RefPtr<Gdk::Pixbuf> imageToPixbuf(const image_t* image);
    /**
     * @brief Converts a Gdk::Pixbuf to an image_t.
     * @note The caller is responsible for deallocating the image.
     */
    image_t* pixbufToImage(const Glib::RefPtr<Gdk::Pixbuf>& pixbuf);
    /**
     * @brief Loads an image_t image from a file.
     * @note The caller is responsible for deallocating the image.
     */
    image_t* loadImageFromFile(const std::string& fileName);
    /**
     * @brief Saves an image_t image to a file.
     */
    void saveImageToFile(const image_t* image, const std::string& fileName, const std::string& format = "png");
    /**
     * @brief Performs test operations on an image. Used for debugging new operators.
     * @note The caller is responsible for deallocating the image.
     */
    image_t* performTestOperations(image_t* src);

}

} // namespace cpparas

#endif /* IMAGEUTILS_HPP */
