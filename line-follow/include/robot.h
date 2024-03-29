// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 3
// Description: Robot class to run the robot.

#pragma once

#include <Bumblebee.h>
#include <vector>
#include "timer.h"
#include "drivetrain.h"
#include "debouncer.h"
#include "pid_controller.h"
#include "light_sensor.h"
#include "neural_network.h"
#include "state_manager.h"
#include "state_handler_tuning.h"
#include "state_handler_pid.h"
#include "state_handler_data_collect.h"
#include "state_handler_data_wait.h"
#include "state_handler_training.h"
#include "state_handler_neural.h"
#include "calibration_data.h"

#define NEURAL_INPUTS 2
#define NEURAL_TOPOLOGY \
    {                   \
        3, 2            \
    }
#define NEURAL_ALPHA 0.2 // 0.3
#define BTN_HOLD_TIME 250

class Robot
{
public:
    Robot();
    ~Robot();

    void setup();
    void run();

private:
    std::vector<struct TrainingData> m_dataPts;

    Drivetrain *m_drivetrain;
    ButtonDebouncer *m_button;
    PID *m_pidController;
    NeuralNetwork *m_neuralNetwork, *m_temp_neuralNetwork;

    TuningMode *m_tuningMode;
    PIDMode *m_pidMode;
    DataCollectMode *m_dataCollectMode;
    DataWaitMode *m_dataWaitMode;
    TrainingMode *m_trainingMode;
    NeuralMode *m_neuralMode;
    StateManager *m_stateManager;

    bool m_buttonPressed;
    bool m_longPressTriggered;
    unsigned long m_buttonPressTime;
    void periodic();

    void when_btn_pressed();
    void when_btn_held();
};
