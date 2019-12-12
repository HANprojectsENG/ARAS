#ifndef STATEMACHINEWIDGET_HPP
#define STATEMACHINEWIDGET_HPP

#include "StateMachine.hpp"
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <memory>

class StateMachineWidget {
public:
    StateMachineWidget(std::shared_ptr<StateMachine> _stateMachine);
    virtual ~StateMachineWidget();
    Gtk::Grid& operator()();

private:
    bool update();
    void on_start_stop_button_clicked();
    void on_simulate_hand_button_clicked();

    std::shared_ptr<StateMachine> stateMachine;
    Gtk::Grid container;
    Gtk::Button startStopButton;
    Gtk::Button simulateHandButton;
    Gtk::Label layerLabel;
    Gtk::Label stepLabel;
    bool paused;
};

#endif /* STATEMACHINEWIDGET_HPP */
