#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include "CoordinateMatrix.hpp"
#include "HandDetection.hpp"
#include "ImageLoader.hpp"
#include "Projection.hpp"
#include "RegionExtractor.hpp"
#include "StudChecker.hpp"
#include "util/GenericStateMachine.hpp"
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

class StateMachine : public GenericStateMachine<State> {
public:
    StateMachine();
    ~StateMachine();

    void init();

protected:
    bool continueCondition();

private:
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
};

#endif /* STATEMACHINE_HPP */
