#pragma once

#include "state_handler.h"
#include "drivetrain.h"
#include "pid_controller.h"
#include <vector>

class DataWaitMode : public IRobotState
{
public:
    DataWaitMode(Drivetrain *drivetrain, PID *pidController);
    ~DataWaitMode();

    void init() override;
    void periodic() override;
    void postPeriodic() override;
    bool btnPressed() override;
    void btnHeld() override;

private:
    Drivetrain *m_drivetrain;
    PID *m_pidController;

    unsigned long m_lastDataTime;
};
