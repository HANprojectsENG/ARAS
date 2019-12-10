#ifndef IMAGEUTILS_HPP
#define IMAGEUTILS_HPP

#include "operators.h"
#include <gdkmm/pixbuf.h>

namespace ImageUtils {

Glib::RefPtr<Gdk::Pixbuf> imageToPixbuf(const image_t* image);
image_t* pixbufToImage(const Glib::RefPtr<Gdk::Pixbuf>& pixbuf);
image_t* loadImageFromFile(const std::string& fileName);
void saveImageToFile(const image_t* image, const std::string& fileName, const std::string& format = "png");
image_t* performTestOperations(image_t* src);

}

#endif /* IMAGEUTILS_HPP */
