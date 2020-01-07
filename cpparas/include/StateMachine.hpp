#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include "CoordinateMatrix.hpp"
#include "HandDetection.hpp"
#include "ImageLoader.hpp"
#include "LSFParser.hpp"
#include "Locator.hpp"
#include "Projection.hpp"
#include "RegionExtractor.hpp"
#include "StudChecker.hpp"
#include "util/GenericStateMachine.hpp"
#include "util/StateStep.hpp"
#include <map>

namespace cpparas {

enum class State {
    NOT_STARTED,
    INIT,
    STARTING,
    CHECK_CURRENT_STEP,
    PROJECT_STEP,
    WAIT_HAND_ENTER,
    WAIT_HAND_EXIT,
    PROJECT_OFF,
    CAPTURE,
    CHECK_NEXT_STEP,
    FINAL_STEP
};

class StateMachine : public GenericStateMachine<State> {
public:
    StateMachine(std::shared_ptr<Locator> locator_);
    ~StateMachine() override;

    void init() override;
    StateStep getStateStep() const;

    std::shared_ptr<Projection> getProjection() const;

    void setLSFData(const LSFParser::LSFData& data);

    // Encapsulating functions.
    void simulateHand(bool handPresent);

protected:
    bool exitCondition() const override;

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

    void WAIT_HAND_ENTER_entry();
    void WAIT_HAND_ENTER_do();
    void WAIT_HAND_ENTER_exit();

    void WAIT_HAND_EXIT_entry();
    void WAIT_HAND_EXIT_do();
    void WAIT_HAND_EXIT_exit();

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

    StateStep stateStep;
    LSFParser::LSFData lsfData;
    CoordinateMatrix coordinateMatrix;
    HandDetection handDetection;
    std::shared_ptr<Projection> projection;
    std::shared_ptr<Locator> locator;
};

} // namespace cpparas

#endif /* STATEMACHINE_HPP */
