// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 3
// Description: Robot class to run the robot.

#pragma once

#include <Bumblebee.h>
#include "timer.h"
#include "drivetrain.h"
#include "debouncer.h"
#include "pid_controller.h"
#include "light_sensor.h"

#define MAX_DATA_PTS 100

class Robot
{
public:
    Robot();
    ~Robot();

    enum ControllerType
    {
        PID_MODE,
        DATA_MODE,
        TRAINING_MODE,
        NEURAL_NETWORK_MODE
    };

    struct TrainingData
    { // Structure declaration
        u08 left_ir_reading;
        u08 right_ir_reading;
        MotorCommand speeds;
    };

    void setup();
    void run();

private:
    ControllerType m_controllerType;
    Drivetrain m_drivetrain;
    ButtonDebouncer m_button;
    PID m_pidController;

    int m_lastWorkingDir;
    bool m_offTrackMode;
    unsigned long m_offTrackInitTime;
    unsigned long m_offTrackWaitTime;
    struct TrainingData m_data_pts[MAX_DATA_PTS];
    size_t m_num_data_pts = 0;

    void periodic();

    void print_controller_string();
    void when_btn_pressed();
    void data_state_periodic();
    void data_state_init();
    void training_state_init();
    void training_state_periodic();
    void neural_state_init();
    void neural_state_periodic();
    void pid_state_periodic();

    bool m_buttonPressed;
};
