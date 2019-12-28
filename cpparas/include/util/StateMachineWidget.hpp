#ifndef STATEMACHINEWIDGET_HPP
#define STATEMACHINEWIDGET_HPP

#include "StateMachine.hpp"
#include "util/ImageArea.hpp"
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/window.h>
#include <memory>

namespace cpparas {

class StateMachineWidget {
public:
    StateMachineWidget(std::shared_ptr<StateMachine> _stateMachine, std::shared_ptr<ImageLoader> _imageLoader);
    virtual ~StateMachineWidget();
    Gtk::Grid& operator()();

private:
    bool update();
    void on_start_stop_button_clicked();
    void on_simulate_hand_button_toggled();

    std::shared_ptr<StateMachine> stateMachine;
    std::shared_ptr<ImageLoader> imageLoader;
    Gtk::Grid container;
    Gtk::Button startStopButton;
    Gtk::ToggleButton simulateHandButton;
    Gtk::Label layerLabel;
    Gtk::Label stepLabel;
    Gtk::ScrolledWindow imageViewport;
    ImageArea imageArea;
    bool paused;
};

} // namespace cpparas

#endif /* STATEMACHINEWIDGET_HPP */
