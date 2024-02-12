// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 3
// Description: Robot class to run the robot.

#pragma once

#include <Bumblebee.h>
#include "timer.h"
#include "drivetrain.h"
#include "debouncer.h"

class Robot
{
public:
    Robot();
    ~Robot();

    enum ControllerType
    {
        PID,
        DATA,
        TRAINING,
        NEURAL_NETWORK
    };

    void setup();
    void run();

private:
    ControllerType m_controllerType;
    Drivetrain m_drivetrain;
    ButtonDebouncer m_button;

    void periodic();

    void print_controller_string();
    void when_btn_pressed();

    bool m_buttonPressed;
};
