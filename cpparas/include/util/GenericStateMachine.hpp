#ifndef GENERICSTATEMACHINE_HPP
#define GENERICSTATEMACHINE_HPP

#include <functional>
#include <map>

enum class StateFuncType {
    ENTRY,
    DO,
    EXIT
};

template <typename StateT>
class GenericStateMachine {
public:
    bool doCycle()
    {
        performDo();
        if (continueCondition()) {
            return true;
        } else {
            performExit();
            return false;
        }
    }

    StateT getCurrentState()
    {
        return currentState;
    }

protected:
    void addHandler(StateT state, StateFuncType type, std::function<void()> handler)
    {
        handlerFuncs[std::make_pair(state, type)] = handler;
    }
    bool continueCondition()
    {
        return true;
    }
    void setInitialState(StateT state)
    {
        currentState = state;
        performEntry();
    }
    void switchState(StateT newState)
    {
        performExit();
        currentState = newState;
        performEntry();
    }

private:
    void performEntry()
    {
        perform(StateFuncType::ENTRY);
    }
    void performDo()
    {
        perform(StateFuncType::DO);
    }
    void performExit()
    {
        perform(StateFuncType::EXIT);
    }
    void perform(StateFuncType type)
    {
        this->handlerFuncs.at(std::make_pair(currentState, type))();
    }

    StateT currentState;
    std::map<std::pair<StateT, StateFuncType>, std::function<void()>> handlerFuncs;
};

#endif /* GENERICSTATEMACHINE_HPP */
