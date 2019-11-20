#include "MyArea.hpp"
#include <cairomm/context.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <giomm/resource.h>
#include <glibmm/fileutils.h>
#include <iostream>

const uint32_t width = 200;
const uint32_t height = 200;

MyArea::MyArea()
{
    try {
        // Allocate new buffer and fill with pattern.
        uint8_t* data = (uint8_t*)malloc(width * height * 3);
        for (uint32_t i = 0; i < width * height * 3; i++) {
            data[i] = i;
        }
        m_image = Gdk::Pixbuf::create_from_data(data, Gdk::Colorspace::COLORSPACE_RGB, false, 8, width, height, width * 3);
    } catch (const Gio::ResourceError& ex) {
        std::cerr << "ResourceError: " << ex.what() << std::endl;
    } catch (const Gdk::PixbufError& ex) {
        std::cerr << "PixbufError: " << ex.what() << std::endl;
    }

    // Show at least a quarter of the image.
    if (m_image)
        set_size_request(m_image->get_width() / 2, m_image->get_height() / 2);
}

MyArea::~MyArea()
{
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
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

    return true;
}
