#include "util/StateMachineWidget.hpp"

StateMachineWidget::StateMachineWidget(StateMachine* _stateMachine)
    : stateMachine(_stateMachine)
    , container()
    , startButton("Start")
    , simulateHandButton("Simulate hand")
    , layerLabel("Layer: x")
    , stepLabel("Step: y")
{
    container.set_column_spacing(5);
    container.attach(startButton, 1, 1, 1, 1);
    container.attach(simulateHandButton, 2, 1, 1, 1);
    container.attach(layerLabel, 3, 1, 1, 1);
    container.attach(stepLabel, 4, 1, 1, 1);
    startButton.show();
    simulateHandButton.show();
    layerLabel.show();
    stepLabel.show();
}

StateMachineWidget::~StateMachineWidget()
{
}

Gtk::Grid& StateMachineWidget::operator()()
{
    return container;
}
