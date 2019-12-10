#ifndef STATEMACHINEWIDGET_HPP
#define STATEMACHINEWIDGET_HPP

#include "StateMachine.hpp"
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>

class StateMachineWidget {
public:
    StateMachineWidget(StateMachine* _stateMachine);
    ~StateMachineWidget();
    Gtk::Grid& operator()();

private:
    StateMachine* stateMachine;
    Gtk::Grid container;
    Gtk::Button startButton;
    Gtk::Button simulateHandButton;
    Gtk::Label layerLabel;
    Gtk::Label stepLabel;
};

#endif /* STATEMACHINEWIDGET_HPP */
