// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 3
// Description: Robot class to run the robot.

#pragma once

#include <Bumblebee.h>
#include <util/delay.h>
#include <vector>
#include "timer.h"
#include "drivetrain.h"
#include "debouncer.h"
#include "pid_controller.h"
#include "light_sensor.h"
#include "neural_network.h"

#define MAX_DATA_PTS 100
#define NEURAL_INPUTS 2
#define NEURAL_TOPOLOGY \
    {                   \
        3, 2         \
    }

 struct TrainingData
{ // Structure declaration
        u08 left_ir_reading;
        u08 right_ir_reading;
        MotorCommand speeds;
};

class Robot
{
public:
    Robot();
    ~Robot();

    enum ControllerType
    {
        PID_MODE,
        DATA_COLLECT_MODE,
        DATA_WAIT_MODE,
        TRAINING_MODE,
        NEURAL_NETWORK_MODE
    };

    void setup();
    void run();

private:
    ControllerType m_controllerType;
    Drivetrain *m_drivetrain;
    ButtonDebouncer *m_button;
    PID *m_pidController;
    NeuralNetwork *m_neuralNetwork;

    int m_lastWorkingDir;
    bool m_offTrackMode;
    unsigned long m_offTrackInitTime;
    unsigned long m_offTrackWaitTime;
    unsigned long m_lastDataTime;
    std::vector<struct TrainingData> m_data_pts;

    void periodic();

    void print_controller_string();
    void when_btn_pressed();

    void pid_state_periodic();

    void data_state_init();
    void data_collect_state_periodic();
    void data_wait_state_periodic();

    void training_state_init();
    void training_state_periodic();

    void neural_state_init();
    void neural_state_periodic();

    bool m_buttonPressed;
};
