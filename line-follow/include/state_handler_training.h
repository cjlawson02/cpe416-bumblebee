#pragma once

#include "calibration_data.h"
#include "state_handler.h"
#include "drivetrain.h"
#include "pid_controller.h"
#include <time.h>

class TrainingMode : public IRobotState
{
public:
    TrainingMode(NeuralNetwork *nn, NeuralNetwork *temp_nn, std::vector<struct TrainingData> *data_pts, float alpha);
    ~TrainingMode();

    void printTrainingScreen();
    void init() override;
    void periodic() override;
    void postPeriodic() override;
    bool btnPressed() override;
    void btnHeld() override;

private:
    NeuralNetwork *m_neural, *m_temp_neural;
    std::vector<struct TrainingData> *m_data;
    float m_alpha;
    unsigned long m_startTime;
    int m_epoch;
    size_t m_j;

    bool m_editMode = false;
};
