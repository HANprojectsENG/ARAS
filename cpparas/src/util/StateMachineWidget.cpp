#include "util/StateMachineWidget.hpp"
#include "util/ImageUtils.hpp"
#include <glibmm/main.h>

namespace cpparas {

StateMachineWidget::StateMachineWidget(std::shared_ptr<StateMachine> _stateMachine, std::shared_ptr<ImageLoader> _imageLoader)
    : stateMachine(_stateMachine)
    , imageLoader(_imageLoader)
    , container()
    , startStopButton()
    , simulateHandButton("Simulate hand")
    , layerLabel()
    , stepLabel()
    , imageViewport()
    , imageArea()
    , paused(true)
{
    update();

    imageViewport.set_vexpand(true);
    imageViewport.set_hexpand(true);

    imageViewport.add(imageArea);
    container.set_column_spacing(5);
    container.attach(startStopButton, 1, 1, 1, 1);
    container.attach(simulateHandButton, 2, 1, 1, 1);
    container.attach(layerLabel, 3, 1, 1, 1);
    container.attach(stepLabel, 4, 1, 1, 1);
    container.attach(imageViewport, 1, 3, 9, 1);

    imageViewport.show();
    startStopButton.show();
    simulateHandButton.show();
    layerLabel.show();
    stepLabel.show();
    imageArea.show();

    startStopButton.signal_clicked().connect(sigc::mem_fun(*this,
        &StateMachineWidget::on_start_stop_button_clicked));
    simulateHandButton.signal_toggled().connect(sigc::mem_fun(*this,
        &StateMachineWidget::on_simulate_hand_button_toggled));
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
        if (!stateMachine->doCycle()) {
            paused = true;
        }
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
    layerLabel.set_text(std::string("Layer: ") + std::to_string(stateMachine->getStateStep().layer));
    stepLabel.set_text(std::string("Step: ") + std::to_string(stateMachine->getStateStep().step));
    //Check if new frame to show is available, if so, get it from imageLoader and show it
    if (imageLoader->new_UI_frame_available) {
        imageArea.setImage(imageLoader->Get_UI_frame());
    }
    return true;
}

void StateMachineWidget::on_start_stop_button_clicked()
{
    if (stateMachine->getCurrentState() == State::NOT_STARTED) {
        stateMachine->init();
    }
    paused = !paused;
}

void StateMachineWidget::on_simulate_hand_button_toggled()
{
    stateMachine->simulateHand(simulateHandButton.get_active());
}

} // namespace cpparas
