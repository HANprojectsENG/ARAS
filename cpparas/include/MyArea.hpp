#ifndef MYAREA_HPP
#define MYAREA_HPP

#include <gdkmm/pixbuf.h>
#include <gtkmm/drawingarea.h>

class MyArea : public Gtk::DrawingArea {
public:
    MyArea();
    virtual ~MyArea();

protected:
    //Override default signal handler:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    Glib::RefPtr<Gdk::Pixbuf> m_image;
};

#endif /* MYAREA_HPP */
