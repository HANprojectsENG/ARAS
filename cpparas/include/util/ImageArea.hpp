#ifndef IMAGEAREA_HPP
#define IMAGEAREA_HPP

#include "operators.h"
#include <gdkmm/pixbuf.h>
#include <gtkmm/drawingarea.h>

class ImageArea : public Gtk::DrawingArea {
public:
    ImageArea();
    virtual ~ImageArea();
    void setImage(const image_t* image);

protected:
    //Override default signal handler:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    Glib::RefPtr<Gdk::Pixbuf> m_image;
};

#endif /* IMAGEAREA_HPP */
