#include "StateMachine.hpp"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::init()
{
    currentState = State::INIT;
    (this->*ENTRY_FUNCS[currentState])();
}

bool StateMachine::doCycle()
{
    (this->*DO_FUNCS[currentState])();
    // Always continue for now.
    return true;
}

void StateMachine::switchState(State newState)
{
    (this->*EXIT_FUNCS[currentState])();
    currentState = newState;
    (this->*ENTRY_FUNCS[currentState])();
}

void StateMachine::INIT_entry() {}
void StateMachine::INIT_do() {}
void StateMachine::INIT_exit() {}

void StateMachine::STARTING_entry() {}
void StateMachine::STARTING_do() {}
void StateMachine::STARTING_exit() {}

void StateMachine::CHECK_CURRENT_STEP_entry() {}
void StateMachine::CHECK_CURRENT_STEP_do() {}
void StateMachine::CHECK_CURRENT_STEP_exit() {}

void StateMachine::PROJECT_STEP_entry() {}
void StateMachine::PROJECT_STEP_do() {}
void StateMachine::PROJECT_STEP_exit() {}

void StateMachine::WAIT_entry() {}
void StateMachine::WAIT_do() {}
void StateMachine::WAIT_exit() {}

void StateMachine::PROJECT_OFF_entry() {}
void StateMachine::PROJECT_OFF_do() {}
void StateMachine::PROJECT_OFF_exit() {}

void StateMachine::CAPTURE_entry() {}
void StateMachine::CAPTURE_do() {}
void StateMachine::CAPTURE_exit() {}

void StateMachine::CHECK_NEXT_STEP_entry() {}
void StateMachine::CHECK_NEXT_STEP_do() {}
void StateMachine::CHECK_NEXT_STEP_exit() {}

void StateMachine::FINAL_STEP_entry() {}
void StateMachine::FINAL_STEP_do() {}
void StateMachine::FINAL_STEP_exit() {}
