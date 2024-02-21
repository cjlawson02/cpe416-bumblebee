#pragma once

#include "state_handler.h"

class StateManager
{
public:
    StateManager()
    {
    }

    ~StateManager()
    {
        delete m_currentState;
    }

    void switchState(IRobotState *newState, bool shouldKeep = false)
    {
        if (m_currentState != nullptr)
        {
            if (!m_keepCurrentState)
            {
                delete m_currentState;
            }
        }

        m_keepCurrentState = shouldKeep;
        m_currentState = newState;
        m_currentState->init(); // Initialize the new state right after switching
    }

    void update()
    {
        if (m_currentState != nullptr)
        {
            m_currentState->periodic(); // Call the periodic method of the current state
        }
    }

    void post()
    {
        if (m_currentState != nullptr)
        {
            m_currentState->postPeriodic(); // Call the postPeriodic method
        }
    }

    bool btnPressedSignal()
    {
        if (m_currentState != nullptr)
        {
            return m_currentState->btnPressed();
        }

        return true;
    }

    void btnHeldSignal()
    {
        if (m_currentState != nullptr)
        {
            m_currentState->btnHeld();
        }
    }

    RobotState getCurrentState()
    {
        return m_currentState->getState();
    }

private:
    IRobotState *m_currentState = nullptr;
    bool m_keepCurrentState = false;
};
