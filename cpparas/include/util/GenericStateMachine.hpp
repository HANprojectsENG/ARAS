#ifndef GENERICSTATEMACHINE_HPP
#define GENERICSTATEMACHINE_HPP

#include "debug/Debug.hpp"
#include <exception>
#include <functional>
#include <map>

namespace cpparas {

enum class StateFuncType {
    ENTRY,
    DO,
    EXIT
};

const std::map<StateFuncType, std::string> STATE_FUNC_TYPE_NAMES = {
    { StateFuncType::ENTRY, "entry" },
    { StateFuncType::DO, "do" },
    { StateFuncType::EXIT, "exit" }
};

template <typename StateT>
class GenericStateMachine {
public:
    GenericStateMachine(StateT notStartedState) { currentState = notStartedState; };
    virtual ~GenericStateMachine() {};
    virtual void init() = 0;

    bool doCycle()
    {
        if (exitCondition()) {
            throw std::logic_error("state machine has already exited");
        }

        perform(StateFuncType::DO);
        if (!exitCondition()) {
            return true;
        } else {
            perform(StateFuncType::EXIT);
            return false;
        }
    }

    StateT getCurrentState() const
    {
        return currentState;
    }

    std::string getCurrentStateName() const
    {
        std::string stateName;
        if (stateNames.count(currentState) == 1) {
            stateName = stateNames.at(currentState);
        } else {
            stateName = std::to_string((int)currentState);
        }
        return stateName;
    }

protected:
    void addHandler(StateT state, StateFuncType type, std::function<void()> handler)
    {
        handlerFuncs[std::make_pair(state, type)] = handler;
    }
    void addStateName(StateT state, std::string name)
    {
        stateNames[state] = name;
    }
    virtual bool exitCondition() const = 0;
    void setInitialState(StateT state)
    {
        currentState = state;
        perform(StateFuncType::ENTRY);
    }
    void switchState(StateT newState)
    {
        perform(StateFuncType::EXIT);
        currentState = newState;
        perform(StateFuncType::ENTRY);
    }

private:
    void perform(StateFuncType type)
    {
        std::string stateName = getCurrentStateName();
        Debug::println(std::string("Performing state " + stateName + std::string(" ") + STATE_FUNC_TYPE_NAMES.at(type)));
        this->handlerFuncs.at(std::make_pair(currentState, type))();
    }

    StateT currentState;
    std::map<std::pair<StateT, StateFuncType>, std::function<void()>> handlerFuncs {};
    std::map<StateT, std::string> stateNames {};
};

} // namespace cpparas

#endif /* GENERICSTATEMACHINE_HPP */
