#include "util/ImageArea.hpp"
#include "operators.h"
#include "util/ImageUtils.hpp"
#include <cairomm/context.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <giomm/resource.h>
#include <glibmm/fileutils.h>
#include <iostream>

ImageArea::ImageArea()
{
}

ImageArea::~ImageArea()
{
}

void ImageArea::setImage(image_t* image)
{
    try {
        m_image = ImageUtils::imageToPixbuf(image);
        this->set_size_request(m_image->get_width(), m_image->get_height());
    } catch (const Gio::ResourceError& ex) {
        std::cerr << "ResourceError: " << ex.what() << std::endl;
    } catch (const Gdk::PixbufError& ex) {
        std::cerr << "PixbufError: " << ex.what() << std::endl;
    }
}

bool ImageArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    if (!m_image)
        return false;

    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    // Draw the image in the middle of the drawing area, or (if the image is
    // larger than the drawing area) draw the middle part of the image.
    Gdk::Cairo::set_source_pixbuf(cr, m_image,
        (width - m_image->get_width()) / 2, (height - m_image->get_height()) / 2);
    cr->paint();
    this->queue_draw();

    return true;
}
