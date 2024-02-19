#pragma once

#include <vector>
#include "state_handler.h"
#include "drivetrain.h"
#include "pid_controller.h"

class DataCollectMode : public IRobotState
{
public:
    DataCollectMode(Drivetrain *drivetrain, PID *pidController, std::vector<struct TrainingData> *data);
    ~DataCollectMode();

    void init() override;
    void periodic() override;
    void postPeriodic() override;

private:
    Drivetrain *m_drivetrain;
    PID *m_pidController;

    unsigned long m_lastDataTime;
    std::vector<struct TrainingData> *m_data;
};
