#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include "CoordinateMatrix.hpp"
#include "HandDetection.hpp"
#include "ImageLoader.hpp"
#include "Projection.hpp"
#include "RegionExtractor.hpp"
#include "StudChecker.hpp"
#include <map>

enum class State {
    INIT = 0,
    STARTING = 1,
    CHECK_CURRENT_STEP = 2,
    PROJECT_STEP = 3,
    WAIT = 4,
    PROJECT_OFF = 5,
    CAPTURE = 6,
    CHECK_NEXT_STEP = 7,
    FINAL_STEP = 8
};

const std::map<State, std::string> STATE_NAMES = {
    { State::INIT, "Init" },
    { State::STARTING, "Starting" },
    { State::CHECK_CURRENT_STEP, "Check Current Step" },
    { State::PROJECT_STEP, "Project Step" },
    { State::WAIT, "Wait" },
    { State::PROJECT_OFF, "Project Off" },
    { State::CAPTURE, "Capture" },
    { State::CHECK_NEXT_STEP, "Check Next Step" },
    { State::FINAL_STEP, "Final Step" }
};

class StateMachine {
public:
    StateMachine();
    ~StateMachine();

    void init();
    bool doCycle();

private:
    void performEntry();
    void performDo();
    void performExit();
    void switchState(State newState);

    void INIT_entry();
    void INIT_do();
    void INIT_exit();

    void STARTING_entry();
    void STARTING_do();
    void STARTING_exit();

    void CHECK_CURRENT_STEP_entry();
    void CHECK_CURRENT_STEP_do();
    void CHECK_CURRENT_STEP_exit();

    void PROJECT_STEP_entry();
    void PROJECT_STEP_do();
    void PROJECT_STEP_exit();

    void WAIT_entry();
    void WAIT_do();
    void WAIT_exit();

    void PROJECT_OFF_entry();
    void PROJECT_OFF_do();
    void PROJECT_OFF_exit();

    void CAPTURE_entry();
    void CAPTURE_do();
    void CAPTURE_exit();

    void CHECK_NEXT_STEP_entry();
    void CHECK_NEXT_STEP_do();
    void CHECK_NEXT_STEP_exit();

    void FINAL_STEP_entry();
    void FINAL_STEP_do();
    void FINAL_STEP_exit();

    std::map<State, void (StateMachine::*)()> ENTRY_FUNCS {
        { State::INIT, &StateMachine::INIT_entry },
        { State::STARTING, &StateMachine::STARTING_entry },
        { State::CHECK_CURRENT_STEP, &StateMachine::CHECK_CURRENT_STEP_entry },
        { State::PROJECT_STEP, &StateMachine::PROJECT_STEP_entry },
        { State::WAIT, &StateMachine::WAIT_entry },
        { State::PROJECT_STEP, &StateMachine::PROJECT_STEP_entry },
        { State::CAPTURE, &StateMachine::CAPTURE_entry },
        { State::CHECK_NEXT_STEP, &StateMachine::CHECK_NEXT_STEP_entry },
        { State::FINAL_STEP, &StateMachine::FINAL_STEP_entry }
    };
    std::map<State, void (StateMachine::*)()> DO_FUNCS {
        { State::INIT, &StateMachine::INIT_do },
        { State::STARTING, &StateMachine::STARTING_do },
        { State::CHECK_CURRENT_STEP, &StateMachine::CHECK_CURRENT_STEP_do },
        { State::PROJECT_STEP, &StateMachine::PROJECT_STEP_do },
        { State::WAIT, &StateMachine::WAIT_do },
        { State::PROJECT_STEP, &StateMachine::PROJECT_STEP_do },
        { State::CAPTURE, &StateMachine::CAPTURE_do },
        { State::CHECK_NEXT_STEP, &StateMachine::CHECK_NEXT_STEP_do },
        { State::FINAL_STEP, &StateMachine::FINAL_STEP_do }
    };
    std::map<State, void (StateMachine::*)()> EXIT_FUNCS {
        { State::INIT, &StateMachine::INIT_exit },
        { State::STARTING, &StateMachine::STARTING_exit },
        { State::CHECK_CURRENT_STEP, &StateMachine::CHECK_CURRENT_STEP_exit },
        { State::PROJECT_STEP, &StateMachine::PROJECT_STEP_exit },
        { State::WAIT, &StateMachine::WAIT_exit },
        { State::PROJECT_STEP, &StateMachine::PROJECT_STEP_exit },
        { State::CAPTURE, &StateMachine::CAPTURE_exit },
        { State::CHECK_NEXT_STEP, &StateMachine::CHECK_NEXT_STEP_exit },
        { State::FINAL_STEP, &StateMachine::FINAL_STEP_exit }
    };

    State currentState;
};

#endif /* STATEMACHINE_HPP */
