#ifndef CONTROLUI_HPP
#define CONTROLUI_HPP

#include "ImageLoader.hpp"
#include "LSFParser.hpp"
#include "StateMachine.hpp"
#include "util/ImageArea.hpp"
#include <gtkmm/button.h>
#include <gtkmm/window.h>

class ControlUI : public Gtk::Window {
public:
    ControlUI();
    virtual ~ControlUI();

private:
    void on_button_clicked();
    ImageArea area;
    image_t* displayImage;
};

#endif /* CONTROLUI_HPP */
