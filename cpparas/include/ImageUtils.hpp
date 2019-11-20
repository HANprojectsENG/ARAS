#ifndef IMAGEUTILS_HPP
#define IMAGEUTILS_HPP

#include "operators.h"
#include <gdkmm/pixbuf.h>

namespace ImageUtils {

Glib::RefPtr<Gdk::Pixbuf> imageToPixbuf(image_t* image);

}

#endif /* IMAGEUTILS_HPP */
