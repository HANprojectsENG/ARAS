#include "util/ImageUtils.hpp"
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

image_t* pixbufToImage(const Glib::RefPtr<Gdk::Pixbuf>& pixbuf)
{
    if (pixbuf->get_colorspace() != Gdk::Colorspace::COLORSPACE_RGB) {
        throw std::invalid_argument("pixbuf color space is not COLORSPACE_RGB");
    }
    image_t* result = newRGB888Image(pixbuf->get_width(), pixbuf->get_height());
    int rowstride = pixbuf->get_rowstride();
    guint8* pixels = pixbuf->get_pixels();
    for (int row = 0; row < pixbuf->get_height(); row++) {
        for (int col = 0; col < pixbuf->get_width(); col++) {
            rgb888_pixel_t color;
            std::size_t offset = row * rowstride + col * 3;
            color.r = pixels[offset];
            color.g = pixels[offset + 1];
            color.b = pixels[offset + 2];
            setRGB888Pixel(result, col, row, color);
        }
    }
    return result;
}

image_t* loadImageFromFile(const std::string& fileName)
{
    auto pixbuf = Gdk::Pixbuf::create_from_file(fileName);
    return pixbufToImage(pixbuf);
}

image_t* performTestOperations(image_t* src)
{
    image_t* dst = newRGB888Image(src->cols, src->rows);
    copy(src, dst);
    return dst;
}

}
