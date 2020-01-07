#include "StateMachine.hpp"
#include "debug/Debug.hpp"
#include <iostream>

namespace cpparas {

StateMachine::StateMachine(std::shared_ptr<Locator> locator_)
    : GenericStateMachine<State>(State::NOT_STARTED)
    , stateStep()
    , lsfData()
    , coordinateMatrix(DEFAULT_CALIBRATION)
    , handDetection()
    , projection(std::make_shared<Projection>(DEFAULT_CALIBRATION))
    , locator(locator_)
{
    addStateName(State::NOT_STARTED, "Not Started");
    addStateName(State::INIT, "Init");
    addStateName(State::STARTING, "Starting");
    addStateName(State::CHECK_CURRENT_STEP, "Check Current Step");
    addStateName(State::PROJECT_STEP, "Project Step");
    addStateName(State::WAIT_HAND_ENTER, "Wait Hand Enter");
    addStateName(State::WAIT_HAND_EXIT, "Wait Hand Exit");
    addStateName(State::PROJECT_OFF, "Project Off");
    addStateName(State::CAPTURE, "Capture");
    addStateName(State::CHECK_NEXT_STEP, "Check Next Step");
    addStateName(State::FINAL_STEP, "Final Step");

    addHandler(State::INIT, StateFuncType::ENTRY, std::bind(&StateMachine::INIT_entry, this));
    addHandler(State::INIT, StateFuncType::DO, std::bind(&StateMachine::INIT_do, this));
    addHandler(State::INIT, StateFuncType::EXIT, std::bind(&StateMachine::INIT_exit, this));

    addHandler(State::STARTING, StateFuncType::ENTRY, std::bind(&StateMachine::STARTING_entry, this));
    addHandler(State::STARTING, StateFuncType::DO, std::bind(&StateMachine::STARTING_do, this));
    addHandler(State::STARTING, StateFuncType::EXIT, std::bind(&StateMachine::STARTING_exit, this));

    addHandler(State::CHECK_CURRENT_STEP, StateFuncType::ENTRY, std::bind(&StateMachine::CHECK_CURRENT_STEP_entry, this));
    addHandler(State::CHECK_CURRENT_STEP, StateFuncType::DO, std::bind(&StateMachine::CHECK_CURRENT_STEP_do, this));
    addHandler(State::CHECK_CURRENT_STEP, StateFuncType::EXIT, std::bind(&StateMachine::CHECK_CURRENT_STEP_exit, this));

    addHandler(State::PROJECT_STEP, StateFuncType::ENTRY, std::bind(&StateMachine::PROJECT_STEP_entry, this));
    addHandler(State::PROJECT_STEP, StateFuncType::DO, std::bind(&StateMachine::PROJECT_STEP_do, this));
    addHandler(State::PROJECT_STEP, StateFuncType::EXIT, std::bind(&StateMachine::PROJECT_STEP_exit, this));

    addHandler(State::WAIT_HAND_ENTER, StateFuncType::ENTRY, std::bind(&StateMachine::WAIT_HAND_ENTER_entry, this));
    addHandler(State::WAIT_HAND_ENTER, StateFuncType::DO, std::bind(&StateMachine::WAIT_HAND_ENTER_do, this));
    addHandler(State::WAIT_HAND_ENTER, StateFuncType::EXIT, std::bind(&StateMachine::WAIT_HAND_ENTER_exit, this));

    addHandler(State::WAIT_HAND_EXIT, StateFuncType::ENTRY, std::bind(&StateMachine::WAIT_HAND_EXIT_entry, this));
    addHandler(State::WAIT_HAND_EXIT, StateFuncType::DO, std::bind(&StateMachine::WAIT_HAND_EXIT_do, this));
    addHandler(State::WAIT_HAND_EXIT, StateFuncType::EXIT, std::bind(&StateMachine::WAIT_HAND_EXIT_exit, this));

    addHandler(State::PROJECT_OFF, StateFuncType::ENTRY, std::bind(&StateMachine::PROJECT_OFF_entry, this));
    addHandler(State::PROJECT_OFF, StateFuncType::DO, std::bind(&StateMachine::PROJECT_OFF_do, this));
    addHandler(State::PROJECT_OFF, StateFuncType::EXIT, std::bind(&StateMachine::PROJECT_OFF_exit, this));

    addHandler(State::CAPTURE, StateFuncType::ENTRY, std::bind(&StateMachine::CAPTURE_entry, this));
    addHandler(State::CAPTURE, StateFuncType::DO, std::bind(&StateMachine::CAPTURE_do, this));
    addHandler(State::CAPTURE, StateFuncType::EXIT, std::bind(&StateMachine::CAPTURE_exit, this));

    addHandler(State::CHECK_NEXT_STEP, StateFuncType::ENTRY, std::bind(&StateMachine::CHECK_NEXT_STEP_entry, this));
    addHandler(State::CHECK_NEXT_STEP, StateFuncType::DO, std::bind(&StateMachine::CHECK_NEXT_STEP_do, this));
    addHandler(State::CHECK_NEXT_STEP, StateFuncType::EXIT, std::bind(&StateMachine::CHECK_NEXT_STEP_exit, this));

    addHandler(State::FINAL_STEP, StateFuncType::ENTRY, std::bind(&StateMachine::FINAL_STEP_entry, this));
    addHandler(State::FINAL_STEP, StateFuncType::DO, std::bind(&StateMachine::FINAL_STEP_do, this));
    addHandler(State::FINAL_STEP, StateFuncType::EXIT, std::bind(&StateMachine::FINAL_STEP_exit, this));
}

StateMachine::~StateMachine()
{
}

void StateMachine::init()
{
    setInitialState(State::INIT);
}

bool StateMachine::exitCondition() const
{
    return getCurrentState() == State::FINAL_STEP;
}

StateStep StateMachine::getStateStep() const
{
    return stateStep;
}

std::shared_ptr<Projection> StateMachine::getProjection() const
{
    return projection;
}

void StateMachine::setLSFData(const LSFParser::LSFData& data)
{
    lsfData = data;
}

void StateMachine::simulateHand(bool handPresent)
{
    handDetection.simulateHand(handPresent);
}

// State machine actions

void StateMachine::INIT_entry()
{
    // Load save file

    // Spawn camera-locator thread
    locator->Start_Locator_thread();
}
void StateMachine::INIT_do()
{
    // if (cameraWarmUpTimer->expired()) {
    switchState(State::STARTING);
    // }
}
void StateMachine::INIT_exit() {}

void StateMachine::STARTING_entry()
{
    stateStep = StateStep::fromFile();
    if (stateStep.layer == -1)
        stateStep.layer = 0;
    if (stateStep.step == -1)
        stateStep.step = 0;
    switchState(State::CHECK_CURRENT_STEP);
}
void StateMachine::STARTING_do() {}
void StateMachine::STARTING_exit() {}

void StateMachine::CHECK_CURRENT_STEP_entry()
{
    // recognise image
    // if (step successfully completed) {
    switchState(State::PROJECT_STEP);
    // } else {
    //switchState(State::CHECK_NEXT_STEP);
    // }
}
void StateMachine::CHECK_CURRENT_STEP_do() {}
void StateMachine::CHECK_CURRENT_STEP_exit() {}

void StateMachine::PROJECT_STEP_entry()
{
    projection->clear();
    // TODO: Calculate brick shape from current lsf data, layer and step.
    const Brick currentBrick = { Color::ORANGE, 6, 2 };
    projection->showOutline(currentBrick, 20, 30, 0);
    const std::vector<Brick> testBricks = {
        currentBrick,
        { Color::RED, 2, 2 },
        { Color::GREEN, 4, 2 },
        { Color::ORANGE, 2, 2 },
        { Color::GREEN, 3, 2 },
        { Color::BLUE, 4, 2 }
    };
    projection->showInfo(stateStep, testBricks);
    projection->complete();
}
void StateMachine::PROJECT_STEP_do()
{
    // if (timer->expired()) {
    switchState(State::WAIT_HAND_ENTER);
    // }
}
void StateMachine::PROJECT_STEP_exit() {}

void StateMachine::WAIT_HAND_ENTER_entry() {}
void StateMachine::WAIT_HAND_ENTER_do()
{
    image_t* axne = locator->Get_new_frame();
    handDetection.update(axne);
    locator->Send_frame_to_ui(axne);
    if (handDetection.containsHand()) {
        switchState(State::WAIT_HAND_EXIT);
    }
}
void StateMachine::WAIT_HAND_ENTER_exit() {}

void StateMachine::WAIT_HAND_EXIT_entry() {}
void StateMachine::WAIT_HAND_EXIT_do()
{
    image_t* axne = locator->Get_new_frame();
    handDetection.update(axne);
    locator->Send_frame_to_ui(axne);
    if (!handDetection.containsHand()) {
        switchState(State::PROJECT_OFF);
    }
}
void StateMachine::WAIT_HAND_EXIT_exit() {}

void StateMachine::PROJECT_OFF_entry()
{
    // Turn off projector
    projection->clear();
    projection->complete();

    switchState(State::CAPTURE);
}
void StateMachine::PROJECT_OFF_do() {}
void StateMachine::PROJECT_OFF_exit() {}

void StateMachine::CAPTURE_entry()
{
    // Capture image TESTING ONLY
    //ask locator for new frame
    image_t* axne = locator->Get_new_frame();
    //send received frame to locator to be send over to the ui
    locator->Send_frame_to_ui(axne);

    // Check whether step is completed
    //
    switchState(State::CHECK_CURRENT_STEP);
}
void StateMachine::CAPTURE_do() {}
void StateMachine::CAPTURE_exit() {}

void StateMachine::CHECK_NEXT_STEP_entry()
{
    // Save last step
    stateStep.saveToFile();

    // int nextStep = step + 1;
    if (lsfData.Layer.count(stateStep.layer) > 0 && lsfData.Layer.at(stateStep.layer).Step.count(stateStep.step + 1) > 0) {
        stateStep.step += 1;
        switchState(State::CHECK_CURRENT_STEP);
    } else if (lsfData.Layer.count(stateStep.layer + 1) > 0) {
        stateStep.layer += 1;
        stateStep.step = 0;
        switchState(State::CHECK_CURRENT_STEP);
    } else {
        switchState(State::FINAL_STEP);
    }
}
void StateMachine::CHECK_NEXT_STEP_do() {}
void StateMachine::CHECK_NEXT_STEP_exit() {}

void StateMachine::FINAL_STEP_entry()
{
    // Clear save file.
    StateStep::deleteFile();

    Debug::println("You reached the end.");

    // Join camera thread.
}
void StateMachine::FINAL_STEP_do() {}
void StateMachine::FINAL_STEP_exit() {}

} // namespace cpparas
