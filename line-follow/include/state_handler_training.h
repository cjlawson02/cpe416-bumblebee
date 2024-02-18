#pragma once

#include "state_handler.h"
#include "drivetrain.h"
#include "pid_controller.h"

class TrainingMode : public IRobotState
{
public:
    TrainingMode(Drivetrain *drivetrain, PID *pidController);
    ~TrainingMode();

    void init() override;
    void periodic() override;
    void postPeriodic() override;

private:
    Drivetrain *m_drivetrain;
    PID *m_pidController;
};
