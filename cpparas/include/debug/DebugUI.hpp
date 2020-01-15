#ifndef DEBUGUI_HPP
#define DEBUGUI_HPP

#include "StateMachine.hpp"
#include "util/ImageArea.hpp"
#include <gtkmm/grid.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include <gtkmm/window.h>
#include <memory>

namespace cpparas {

class DebugUI : public Gtk::Window {
public:
    DebugUI(std::shared_ptr<StateMachine> stateMachine_);
    virtual ~DebugUI();

private:
    bool update();

    std::shared_ptr<StateMachine> stateMachine;
    Gtk::Grid widgetContainer;
    Gtk::ScrolledWindow logViewport;
    Gtk::TextView logTextView;
    Gtk::Label stateNameLabel;
    Gtk::ScrolledWindow imageViewport;
    Gtk::Grid imageContainer;
    ImageArea imageArea;
    const image_t* currentImage;
};

} // namespace cpparas

#endif /* DEBUGUI_HPP */
