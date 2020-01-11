#ifndef IMAGEAREA_HPP
#define IMAGEAREA_HPP

#include "operators.h"
#include <gdkmm/pixbuf.h>
#include <gtkmm/drawingarea.h>

namespace cpparas {

class ImageArea : public Gtk::DrawingArea {
public:
    /**
     * @brief Creates a GTK widget that displays an image_t image.
     */
    ImageArea();
    virtual ~ImageArea();
    void setImage(const image_t* image);

protected:
    //Override default signal handler:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    Glib::RefPtr<Gdk::Pixbuf> m_image;
};

} // namespace cpparas

#endif /* IMAGEAREA_HPP */
