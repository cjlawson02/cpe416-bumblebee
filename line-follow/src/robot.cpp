// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 3
// Description: Robot class to run the robot.

#include "robot.h"

Robot::Robot() : m_controllerType(PID_MODE), m_drivetrain(Drivetrain(SERVO0_PIN, SERVO1_PIN)), m_button(ButtonDebouncer(10)), m_pid_controller(PID(25.0, 0.0, 1.0))
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
    pid_state_init();
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

void Robot::run_state_periodic(){
    switch (m_controllerType)
    {
    case PID_MODE:
        pid_state_periodic();
        break;
    case DATA:
        data_state_periodic();
        break;
    case TRAINING:
        break;
    case NEURAL_NETWORK:
        break;
    default:
        break;
    }
}

void Robot::periodic()
{
    run_state_periodic();
  
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
    case PID_MODE:
        data_state_init();
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
//Continously called functions;
void Robot::pid_state_periodic()
{
    float error = m_pid_controller.calcOutputWithError(get_IR_diff());
    m_drivetrain.set_speed_turn(15,error);
    lcd_cursor(0, 1);
    print_num((u16)error);
}

void Robot::data_state_init()
{
    m_drivetrain.stop();
}

void Robot::data_state_periodic()
{
    struct MotorCommand speeds;
    speeds = m_drivetrain.compute_proportional(m_pid_controller, 15, get_left_IR_raw(), get_right_IR_raw());
    lcd_cursor(0, 1);
    print_num((u16)speeds.left_speed);
}

void Robot::pid_state_init()
{
}

void Robot::print_controller_string()
{
    clear_screen();
    switch (m_controllerType)
    {
    case PID_MODE:
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
 