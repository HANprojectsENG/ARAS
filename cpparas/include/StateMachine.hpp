#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include "CoordinateMatrix.hpp"
#include "HandDetection.hpp"
#include "ImageLoader.hpp"
#include "LSFParser.hpp"
#include "Projection.hpp"
#include "RegionExtractor.hpp"
#include "StudChecker.hpp"
#include "util/GenericStateMachine.hpp"
#include <map>

enum class State {
    NOT_STARTED,
    INIT,
    STARTING,
    CHECK_CURRENT_STEP,
    PROJECT_STEP,
    WAIT,
    PROJECT_OFF,
    CAPTURE,
    CHECK_NEXT_STEP,
    FINAL_STEP
};

class StateMachine : public GenericStateMachine<State> {
public:
    StateMachine();
    ~StateMachine() override;

    void init() override;
    int getStep();
    int getLayer();

    void setLSFData(const LSFParser::LSFData& data);

    // Encapsulating functions.
    void simulateHand(bool handPresent);

protected:
    bool exitCondition() override;

private:
    void on_start_button_clicked();
    void on_simulate_hand_button_clicked();

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

    int layer;
    int step;
    LSFParser::LSFData lsfData;
    CoordinateMatrix coordinateMatrix;
    HandDetection handDetection;
};

#endif /* STATEMACHINE_HPP */
