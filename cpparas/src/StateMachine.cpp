#include "StateMachine.hpp"
#include "debug/Debug.hpp"
#include <iostream>

namespace cpparas {

StateMachine::StateMachine(std::shared_ptr<Locator> locator_)
    : GenericStateMachine<State>(State::NOT_STARTED)
    , simulatedBaseplateShifted(false)
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
    addStateName(State::CHECK_NEXT_STEP, "Check Next Step");
    addStateName(State::MOVE_BASEPLATE, "Move Baseplate");
    addStateName(State::FINAL_STEP, "Final Step");

    setDoHook(std::bind(&StateMachine::doHook, this));

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

    addHandler(State::CHECK_NEXT_STEP, StateFuncType::ENTRY, std::bind(&StateMachine::CHECK_NEXT_STEP_entry, this));
    addHandler(State::CHECK_NEXT_STEP, StateFuncType::DO, std::bind(&StateMachine::CHECK_NEXT_STEP_do, this));
    addHandler(State::CHECK_NEXT_STEP, StateFuncType::EXIT, std::bind(&StateMachine::CHECK_NEXT_STEP_exit, this));

    addHandler(State::MOVE_BASEPLATE, StateFuncType::ENTRY, std::bind(&StateMachine::MOVE_BASEPLATE_entry, this));
    addHandler(State::MOVE_BASEPLATE, StateFuncType::DO, std::bind(&StateMachine::MOVE_BASEPLATE_do, this));
    addHandler(State::MOVE_BASEPLATE, StateFuncType::EXIT, std::bind(&StateMachine::MOVE_BASEPLATE_exit, this));

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

void StateMachine::simulateBaseplateShifted(bool shifted)
{
    simulatedBaseplateShifted = shifted;
}

// Private functions

std::pair<bool, StateStep> StateMachine::nextStateStep(StateStep fromStep) const
{
    StateStep nextStep = fromStep;
    if (lsfData.Layer.count(fromStep.layer) > 0 && lsfData.Layer.at(fromStep.layer).Step.count(fromStep.step + 1) > 0) {
        nextStep.step += 1;
        return std::make_pair(true, nextStep);
    } else if (lsfData.Layer.count(fromStep.layer + 1) > 0) {
        nextStep.layer += 1;
        nextStep.step = 0;
        return std::make_pair(true, nextStep);
    } else {
        return std::make_pair(false, nextStep);
    }
}

// State machine actions

void StateMachine::doHook()
{
    State currentState = getCurrentState();
    if (currentState != State::INIT && currentState != State::STARTING && currentState != State::FINAL_STEP && currentState != State::MOVE_BASEPLATE) {
        if (simulatedBaseplateShifted || locator->Location_checker()) {
            switchState(State::MOVE_BASEPLATE);
        }
    }
}

void StateMachine::INIT_entry()
{
    // Spawn camera-locator thread
    locator->Start_Locator_thread();

    // Load save file
    stateStep = StateStep::fromFile();
}
void StateMachine::INIT_do()
{
    if (stateStep.layer != -1 && stateStep.step != -1) {
        switchState(State::CHECK_NEXT_STEP);
    } else {
        switchState(State::STARTING);
    }
}
void StateMachine::INIT_exit() {}

void StateMachine::STARTING_entry()
{
    if (stateStep.layer == -1)
        stateStep.layer = 0;
    if (stateStep.step == -1)
        stateStep.step = 0;
}
void StateMachine::STARTING_do()
{
    switchState(State::CHECK_CURRENT_STEP);
}
void StateMachine::STARTING_exit() {}

void StateMachine::CHECK_CURRENT_STEP_entry() {}
void StateMachine::CHECK_CURRENT_STEP_do()
{
    image_t* axne = locator->Get_new_frame();
    locator->Send_frame_to_ui(axne);

    // Calculate coordinate matrix
    coordinateMatrix.update(0, 0, axne->cols, axne->rows);

    // recognise image
    const LSFParser::LSFDataStruct& stepinst = lsfData.Layer.at(stateStep.layer).Step.at(stateStep.step);
    bool brickPlacedCorrectly = StudChecker::matches(axne, coordinateMatrix, stepinst.coordinates, stepinst.layer, stepinst.color);
    if (brickPlacedCorrectly) {
        switchState(State::CHECK_NEXT_STEP);
    } else {
        switchState(State::PROJECT_STEP);
    }
}
void StateMachine::CHECK_CURRENT_STEP_exit() {}

void StateMachine::PROJECT_STEP_entry()
{
    projection->clear();

    std::pair<Point<uint32_t>, Brick> brickAndCoord = LSFParser::Data_to_brick(lsfData.Layer.at(stateStep.layer).Step.at(stateStep.step));
    const Brick currentBrick = brickAndCoord.second;
    projection->showBaseplateOutline();
    projection->showBrickOutline(currentBrick, brickAndCoord.first.col, brickAndCoord.first.row, 0);

    std::vector<Brick> displayBricks = {
        currentBrick,
    };
    std::pair<bool, StateStep> nextStep = nextStateStep(stateStep);
    while (nextStep.first) {
        displayBricks.push_back(LSFParser::Data_to_brick(lsfData.Layer.at(nextStep.second.layer).Step.at(nextStep.second.step)).second);
        nextStep = nextStateStep(nextStep.second);
    }
    projection->showInfo(stateStep, displayBricks);

    projection->complete();
}
void StateMachine::PROJECT_STEP_do()
{
    switchState(State::WAIT_HAND_ENTER);
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
}
void StateMachine::PROJECT_OFF_do()
{
    switchState(State::CHECK_CURRENT_STEP);
}
void StateMachine::PROJECT_OFF_exit() {}

void StateMachine::CHECK_NEXT_STEP_entry()
{
    // Save last step
    stateStep.saveToFile();
}
void StateMachine::CHECK_NEXT_STEP_do()
{
    std::pair<bool, StateStep> nextStep = nextStateStep(stateStep);
    if (nextStep.first) {
        stateStep = nextStep.second;
        switchState(State::CHECK_CURRENT_STEP);
    } else {
        switchState(State::FINAL_STEP);
    }
}
void StateMachine::CHECK_NEXT_STEP_exit() {}

void StateMachine::MOVE_BASEPLATE_entry()
{
    projection->clear();
    projection->showBaseplateOutline();
    projection->showMoveBaseplateWarning();
    projection->complete();
}
void StateMachine::MOVE_BASEPLATE_do()
{
    image_t* axne = locator->Get_new_frame();
    locator->Send_frame_to_ui(axne);
    if (!simulatedBaseplateShifted && !locator->Location_checker()) {
        switchState(getPreviousState());
    }
}
void StateMachine::MOVE_BASEPLATE_exit()
{
    projection->clear();
    projection->complete();
}

void StateMachine::FINAL_STEP_entry()
{
    // Clear save file.
    StateStep::deleteFile();

    Debug::println("You reached the end.");

    // We don't support restarting the state machine, so we don't need to join the camera thread.
}
void StateMachine::FINAL_STEP_do() {}
void StateMachine::FINAL_STEP_exit() {}

} // namespace cpparas
