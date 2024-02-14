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

    void periodic();

    void print_controller_string();
    void when_btn_pressed();

    bool m_buttonPressed;
};
