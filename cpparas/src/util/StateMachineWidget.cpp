#include "util/StateMachineWidget.hpp"
#include <glibmm/main.h>

StateMachineWidget::StateMachineWidget(std::shared_ptr<StateMachine> _stateMachine)
    : stateMachine(_stateMachine)
    , container()
    , startStopButton()
    , simulateHandButton("Simulate hand")
    , layerLabel()
    , stepLabel()
    , paused(true)
{
    update();

    container.set_column_spacing(5);
    container.attach(startStopButton, 1, 1, 1, 1);
    container.attach(simulateHandButton, 2, 1, 1, 1);
    container.attach(layerLabel, 3, 1, 1, 1);
    container.attach(stepLabel, 4, 1, 1, 1);
    startStopButton.show();
    simulateHandButton.show();
    layerLabel.show();
    stepLabel.show();

    startStopButton.signal_clicked().connect(sigc::mem_fun(*this,
        &StateMachineWidget::on_start_stop_button_clicked));
    simulateHandButton.signal_clicked().connect(sigc::mem_fun(*this,
        &StateMachineWidget::on_simulate_hand_button_clicked));
    Glib::signal_timeout().connect(
        sigc::mem_fun(*this, &StateMachineWidget::update),
        100);
}

StateMachineWidget::~StateMachineWidget()
{
}

Gtk::Grid& StateMachineWidget::operator()()
{
    return container;
}

bool StateMachineWidget::update()
{
    if (stateMachine->getCurrentState() != State::NOT_STARTED && !paused) {
        stateMachine->doCycle();
    }

    if (stateMachine->getCurrentState() == State::NOT_STARTED) {
        startStopButton.set_label("Start");
    } else {
        if (paused) {
            startStopButton.set_label("Resume");
        } else {
            startStopButton.set_label("Pause");
        }
    }
    layerLabel.set_text(std::string("Layer: ") + std::to_string(stateMachine->getLayer()));
    stepLabel.set_text(std::string("Step: ") + std::to_string(stateMachine->getStep()));
    return true;
}

void StateMachineWidget::on_start_stop_button_clicked()
{
    if (stateMachine->getCurrentState() == State::NOT_STARTED) {
        stateMachine->init();
    }
    paused = !paused;
}

void StateMachineWidget::on_simulate_hand_button_clicked()
{
}
