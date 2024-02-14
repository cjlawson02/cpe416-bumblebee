// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 3
// Description: Robot class to run the robot.

#include "robot.h"

Robot::Robot() : m_controllerType(PID), m_drivetrain(Drivetrain(SERVO0_PIN, SERVO1_PIN)), m_button(ButtonDebouncer(10))
{
}

Robot::~Robot()
{
}

void Robot::setup()
{
    init_millis(F_CPU);
    init();
    m_drivetrain.setup();
}

void Robot::run()
{
    clear_screen();
    print_controller_string();

    while (1)
    {
        periodic();
    }
}

void Robot::periodic()
{

    if (m_button.get())
    {
        if (!m_buttonPressed)
        {
            m_buttonPressed = true;
            when_btn_pressed();
        }
    }
    else
    {
        m_buttonPressed = false;
    }
}

void Robot::when_btn_pressed()
{
    switch (m_controllerType)
    {
    case PID:
        m_controllerType = DATA;
        break;
    case DATA:
        m_controllerType = TRAINING;
        break;
    case TRAINING:
        m_controllerType = NEURAL_NETWORK;
        break;
    case NEURAL_NETWORK:
        m_controllerType = TRAINING;
        break;
    default:
        break;
    }

    print_controller_string();
}

void Robot::print_controller_string()
{
    clear_screen();
    switch (m_controllerType)
    {
    case PID:
        print_string("Proportional");
        break;
    case DATA:
        print_string("Data");
        break;
    case TRAINING:
        print_string("Training");
        break;
    case NEURAL_NETWORK:
        print_string("Neural");
        break;
    default:
        break;
    }
}
