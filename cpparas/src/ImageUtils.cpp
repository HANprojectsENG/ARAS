#include "ImageUtils.hpp"
#include "operators.h"
#include <gdkmm/pixbuf.h>
#include <stdexcept>

namespace ImageUtils {

Glib::RefPtr<Gdk::Pixbuf> imageToPixbuf(image_t* image)
{
    if (image->type != IMGTYPE_RGB888) {
        throw std::invalid_argument("image type is not RGB888");
    }
    auto pixBuf = Gdk::Pixbuf::create_from_data((guint8*)image->data, Gdk::Colorspace::COLORSPACE_RGB, false, 8, 0 + image->cols, 0 + image->rows, image->cols * 3);
    return pixBuf;
}

}
