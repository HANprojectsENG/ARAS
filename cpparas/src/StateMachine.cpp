#include "StateMachine.hpp"
#include "util/Debug.hpp"
#include <iostream>

StateMachine::StateMachine()
    : layer(-1)
    , step(-1)
{
    addStateName(State::INIT, "Init");
    addStateName(State::STARTING, "Starting");
    addStateName(State::CHECK_CURRENT_STEP, "Check Current Step");
    addStateName(State::PROJECT_STEP, "Project Step");
    addStateName(State::WAIT, "Wait");
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

    addHandler(State::WAIT, StateFuncType::ENTRY, std::bind(&StateMachine::WAIT_entry, this));
    addHandler(State::WAIT, StateFuncType::DO, std::bind(&StateMachine::WAIT_do, this));
    addHandler(State::WAIT, StateFuncType::EXIT, std::bind(&StateMachine::WAIT_exit, this));

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

bool StateMachine::continueCondition()
{
    return getCurrentState() != State::FINAL_STEP;
}

void StateMachine::INIT_entry()
{
    // Load save file

    // Spawn camera thread
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
    step = 0;
    layer = 0;
    switchState(State::CHECK_CURRENT_STEP);
}
void StateMachine::STARTING_do() {}
void StateMachine::STARTING_exit() {}

void StateMachine::CHECK_CURRENT_STEP_entry()
{
    // recognise image
    // if (completed) {
    switchState(State::PROJECT_STEP);
    // } else {
    // switchState(State::CHECK_NEXT_STEP);
    // }
}
void StateMachine::CHECK_CURRENT_STEP_do() {}
void StateMachine::CHECK_CURRENT_STEP_exit() {}

void StateMachine::PROJECT_STEP_entry() {}
void StateMachine::PROJECT_STEP_do()
{
    // if (timer->expired()) {
    switchState(State::WAIT);
    // }
}
void StateMachine::PROJECT_STEP_exit() {}

void StateMachine::WAIT_entry() {}
void StateMachine::WAIT_do()
{
    // if (timer->expired()) {
    switchState(State::WAIT);
    // }
}
void StateMachine::WAIT_exit() {}

void StateMachine::PROJECT_OFF_entry()
{
    // Turn off projector

    switchState(State::CAPTURE);
}
void StateMachine::PROJECT_OFF_do() {}
void StateMachine::PROJECT_OFF_exit() {}

void StateMachine::CAPTURE_entry()
{
    // Capture image

    switchState(State::CHECK_CURRENT_STEP);
}
void StateMachine::CAPTURE_do() {}
void StateMachine::CAPTURE_exit() {}

void StateMachine::CHECK_NEXT_STEP_entry()
{
    // Save last step

    // int nextStep = step + 1;
}
void StateMachine::CHECK_NEXT_STEP_do() {}
void StateMachine::CHECK_NEXT_STEP_exit() {}

void StateMachine::FINAL_STEP_entry()
{
    // Clear save file.

    Debug::println("You reached the end.");

    // Join camera thread.
}
void StateMachine::FINAL_STEP_do() {}
void StateMachine::FINAL_STEP_exit() {}
