#pragma once

#include "state_handler.h"
#include "pid_controller.h"
#include "drivetrain.h"

class PIDMode : public IRobotState
{
public:
    PIDMode(Drivetrain *drivetrain, PID *pidController);
    ~PIDMode();

    void init() override;
    void periodic() override;
    void postPeriodic() override;

private:
    Drivetrain *m_drivetrain;
    PID *m_pidController;
    int m_lastWorkingDir = 1;
    bool m_offTrackMode = false;
    unsigned long m_offTrackInitTime = 0;
    unsigned long m_offTrackWaitTime = 100;
};
