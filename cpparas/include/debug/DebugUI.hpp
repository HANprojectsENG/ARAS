#ifndef DEBUGUI_HPP
#define DEBUGUI_HPP

#include <gtkmm/grid.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include <gtkmm/window.h>

class DebugUI : public Gtk::Window {
public:
    DebugUI();
    virtual ~DebugUI();

private:
    bool update();

    Gtk::Grid widgetContainer;
    Gtk::ScrolledWindow logViewport;
    Gtk::TextView logTextView;
};

#endif /* DEBUGUI_HPP */
