#pragma once

#include "state_handler.h"
#include "drivetrain.h"
#include "neural_network.h"

class NeuralMode : public IRobotState
{
public:
    NeuralMode(Drivetrain *drivetrain, NeuralNetwork *neuralNetwork);
    ~NeuralMode();

    void init() override;
    void periodic() override;
    void postPeriodic() override;

private:
    Drivetrain *m_drivetrain;
    NeuralNetwork *m_neuralNetwork;
};
