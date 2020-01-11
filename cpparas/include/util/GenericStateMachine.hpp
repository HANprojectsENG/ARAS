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
    /**
     * @brief The constructor for the generic state machine. Requires a not-started state.
     */
    GenericStateMachine(StateT notStartedState) { currentState = notStartedState; };
    virtual ~GenericStateMachine() {};
    /**
     * @brief The initialisation function.
     *        After this function is called, the current state is not the not-started state anymore.
     */
    virtual void init() = 0;

    /**
     * @brief Executes one cycle. This calls the do-handler of the current state.
     * @return Whether the state machine can continue (true) or is done (false).
     */
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

    /**
     * @brief Returns the current state.
     */
    StateT getCurrentState() const
    {
        return currentState;
    }

    /**
     * @brief Returns the name of the current state.
     */
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
    /**
     * @brief Returns whether the state machine can continue.
     *        This usually entails checking whether the state is equal to a "finished state".
     * @return true if the state machine has finished, false if it can continue.
     */
    virtual bool exitCondition() const = 0;

    /**
     * @brief Adds a function handler for a specific state and a specific function type (entry, do, exit).
     */
    void addHandler(StateT state, StateFuncType type, std::function<void()> handler)
    {
        handlerFuncs[std::make_pair(state, type)] = handler;
    }

    /**
     * @brief Registers a name for a given state. Used for debug printing. Not required.
     */
    void addStateName(StateT state, std::string name)
    {
        stateNames[state] = name;
    }

    /**
     * @brief Sets a hook to be called before the do-handler of any state is called.
     *        This hook is seen as part of the do-handler, so switchState will work.
     */
    void setDoHook(std::function<void()> doHookFunc_)
    {
        doHookFunc = doHookFunc_;
    }

    /**
     * @brief Sets the initial state of the state machine (not the not-started state).
     * @note This method should only be called within init().
     */
    void setInitialState(StateT state)
    {
        currentState = state;
        previousState = state;
        perform(StateFuncType::ENTRY);
    }

    /**
     * @brief Switches the current state to another state and calls the corresponding entry and exit functions.
     * @note Can only be called from within a do-handler.
     */
    void switchState(StateT newState)
    {
        if (currentFuncType != StateFuncType::DO) {
            Debug::println(std::string("Performing state " + getCurrentStateName() + std::string(" ") + STATE_FUNC_TYPE_NAMES.at(currentFuncType)));
            throw std::logic_error("cannot switch states outside of a do-handler");
        }
        perform(StateFuncType::EXIT);
        previousState = currentState;
        currentState = newState;
        perform(StateFuncType::ENTRY);
    }

    /**
     * @brief Returns the state before the last switch.
     */
    StateT getPreviousState() const
    {
        return previousState;
    }

private:
    void perform(StateFuncType type)
    {
        std::string stateName = getCurrentStateName();
        Debug::println(std::string("Performing state " + stateName + std::string(" ") + STATE_FUNC_TYPE_NAMES.at(type)));
        currentFuncType = type;
        if (currentFuncType == StateFuncType::DO && doHookFunc) {
            doHookFunc();
        }
        this->handlerFuncs.at(std::make_pair(currentState, type))();
    }

    StateT currentState;
    StateT previousState;
    StateFuncType currentFuncType;

    std::map<std::pair<StateT, StateFuncType>, std::function<void()>> handlerFuncs {};
    std::map<StateT, std::string> stateNames {};
    std::function<void()> doHookFunc;
};

} // namespace cpparas

#endif /* GENERICSTATEMACHINE_HPP */
