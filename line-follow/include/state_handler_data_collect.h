#pragma once

#include <vector>
#include "state_handler.h"
#include "drivetrain.h"
#include "pid_controller.h"

#define MAX_DATA_PTS 126 // determined experimetnally after uploading code

class DataCollectMode : public IRobotState
{
public:
    DataCollectMode(Drivetrain *drivetrain, PID *pidController, std::vector<struct TrainingData> *data);
    ~DataCollectMode();

    void init() override;
    void periodic() override;
    void postPeriodic() override;
    bool btnPressed() override;
    void btnHeld() override;

private:
    Drivetrain *m_drivetrain;
    PID *m_pidController;

    unsigned long m_lastDataTime;
    std::vector<struct TrainingData> *m_data;
};
