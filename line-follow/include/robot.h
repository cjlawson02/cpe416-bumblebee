// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 3
// Description: Robot class to run the robot.

#pragma once

#include <Bumblebee.h>
#include "timer.h"
#include "drivetrain.h"
#include "debouncer.h"
#include "pid_controller.h"

class Robot
{
public:
    Robot();
    ~Robot();

    enum ControllerType
    {
        PID_MODE,
        DATA,
        TRAINING,
        NEURAL_NETWORK
    };

    void setup();
    void run();

private:
    ControllerType m_controllerType;
    Drivetrain m_drivetrain;
    PID m_pid_controller;
    ButtonDebouncer m_button;

    struct TrainingData {   // Structure declaration
        u08 left_ir_reading;
        u08 right_ir_reading;
        float left_speed;          // Member (int variable)
        float right_speed;       
    };

    void periodic();

    void print_controller_string();
    void when_btn_pressed();
    void data_state_periodic();
    void data_state_init();
    void pid_state_periodic();
    void pid_state_init();
    void run_state_periodic();

    bool m_buttonPressed;
};
