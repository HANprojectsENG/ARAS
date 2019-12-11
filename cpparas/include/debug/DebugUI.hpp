#ifndef DEBUGUI_HPP
#define DEBUGUI_HPP

#include "StateMachine.hpp"
#include <gtkmm/grid.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include <gtkmm/window.h>
#include <memory>

class DebugUI : public Gtk::Window {
public:
    DebugUI(StateMachine* stateMachine_);
    virtual ~DebugUI();

private:
    bool update();

    StateMachine* stateMachine;
    Gtk::Grid widgetContainer;
    Gtk::ScrolledWindow logViewport;
    Gtk::TextView logTextView;
    Gtk::Label stateNameLabel;
    Gtk::Label brickPositionLabel;
    Gtk::Label expectedValueLabel;
};

#endif /* DEBUGUI_HPP */
