#pragma once

enum RobotState
{
    TUNING_MODE,
    PID_MODE,
    DATA_COLLECT_MODE,
    DATA_WAIT_MODE,
    TRAINING_MODE,
    NEURAL_NETWORK_MODE
};

class IRobotState
{
public:
    virtual ~IRobotState() {} // Virtual destructor for proper cleanup

    // Require derived classes to implement these methods
    virtual void init() = 0;
    virtual void periodic() = 0;
    virtual void postPeriodic() = 0;
    virtual bool btnPressed() = 0;
    virtual void btnHeld() = 0;

    RobotState getState()
    {
        return m_stateName;
    }

protected:
    RobotState m_stateName;
};
