#include "StateMachine.hpp"
#include "util/Debug.hpp"
#include <iostream>

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::init()
{
    currentState = State::INIT;
    performEntry();
}

bool StateMachine::doCycle()
{
    performDo();
    if (currentState == State::FINAL_STEP) {
        performExit();
        return false;
    } else {
        return true;
    }
}

void StateMachine::performEntry()
{
    Debug::println(std::string("Performing state ") + STATE_NAMES.at(currentState) + std::string(" entry"));
    (this->*ENTRY_FUNCS.at(currentState))();
}

void StateMachine::performDo()
{
    Debug::println(std::string("Performing state ") + STATE_NAMES.at(currentState) + std::string(" do"));
    (this->*DO_FUNCS.at(currentState))();
}

void StateMachine::performExit()
{
    Debug::println(std::string("Performing state ") + STATE_NAMES.at(currentState) + std::string(" exit"));
    (this->*EXIT_FUNCS.at(currentState))();
}

void StateMachine::switchState(State newState)
{
    performExit();
    currentState = newState;
    performEntry();
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
