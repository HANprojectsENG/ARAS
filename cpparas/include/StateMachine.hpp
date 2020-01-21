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
#include <chrono>
#include <map>

namespace cpparas {

const float PROJECT_OFF_DELAY = 1.0f; // Seconds

enum class State {
    NOT_STARTED,
    INIT,
    STARTING,
    CHECK_CURRENT_STEP,
    PROJECT_STEP,
    WAIT_HAND_ENTER,
    WAIT_HAND_EXIT,
    PROJECT_OFF,
    CHECK_NEXT_STEP,
    MOVE_BASEPLATE,
    FINAL_STEP
};

class StateMachine : public GenericStateMachine<State> {
public:
    /**
     * @brief Creates a state machine as seen in the Activity Diagram.
     * @image html ActivityDiagram.png
     */
    StateMachine(std::shared_ptr<Locator> locator_);
    ~StateMachine() override;

    void init() override;

    StateStep getStateStep() const;
    std::shared_ptr<Projection> getProjection() const;

    /**
     * @brief Sets the sequence data to be used in the program.
     * @note Needs to be called before calling the first .update().
     */
    void setLSFData(const LSFParser::LSFData& data);

    void simulateBaseplateShifted(bool baseplateShifted);
    void simulateHand(bool handPresent);

protected:
    bool exitCondition() const override;

private:
    /**
     * @brief Returns the next step in the sequence if available.
     */
    std::pair<bool, StateStep> nextStateStep(StateStep fromStep) const;

    void doHook();

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

    void CHECK_NEXT_STEP_entry();
    void CHECK_NEXT_STEP_do();
    void CHECK_NEXT_STEP_exit();

    void MOVE_BASEPLATE_entry();
    void MOVE_BASEPLATE_do();
    void MOVE_BASEPLATE_exit();

    void FINAL_STEP_entry();
    void FINAL_STEP_do();
    void FINAL_STEP_exit();

    bool simulatedBaseplateShifted;
    std::chrono::time_point<std::chrono::system_clock> projectOffStartTime;
    StateStep stateStep;
    LSFParser::LSFData lsfData;
    CoordinateMatrix coordinateMatrix;
    HandDetection handDetection;
    std::shared_ptr<Projection> projection;
    std::shared_ptr<Locator> locator;
};

} // namespace cpparas

#endif /* STATEMACHINE_HPP */
