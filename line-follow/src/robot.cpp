// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 3
// Description: Robot class to run the robot.

#include "robot.h"
#include <util/delay.h>

Robot::Robot() : m_controllerType(PID_MODE),
                 m_drivetrain(Drivetrain(SERVO0_PIN, SERVO1_PIN)),
                 m_button(ButtonDebouncer(10)),
                 m_pidController(PID(12.0, 0.0, 1.0)),
                 m_lastWorkingDir(1),
                 m_offTrackMode(false),
                 m_offTrackInitTime(0),
                 m_offTrackWaitTime(100)
{
    m_pidController.setBounds(-100, 100);
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
    // Handle controller change
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

    // Controller periodic loop
    switch (m_controllerType)
    {
    case PID_MODE:
        pid_state_periodic();
        break;
    case DATA_MODE:
        data_state_periodic();
        break;
    case TRAINING_MODE:
        break;
    case NEURAL_NETWORK_MODE:
        break;
    default:
        break;
    }
}

void Robot::when_btn_pressed()
{
    switch (m_controllerType)
    {
    case PID_MODE:
        m_controllerType = DATA_MODE;
        data_state_init();
        break;
    case DATA_MODE:
        m_controllerType = TRAINING_MODE;
        training_state_init();
        break;
    case TRAINING_MODE:
        neural_state_init();
        m_controllerType = NEURAL_NETWORK_MODE;
        break;
    case NEURAL_NETWORK_MODE:
        training_state_init();
        m_controllerType = TRAINING_MODE;
        break;
    default:
        break;
    }

    print_controller_string();
}

void Robot::pid_state_periodic()
{
    int dir = m_lastWorkingDir;
    // If off track, sweep left and right
    if (off_track())
    {
        // If we just entered off track mode, set the initial time
        if (!m_offTrackMode)
        {
            m_offTrackInitTime = millis();
            m_offTrackMode = true;
        }

        // Turn in place
        m_drivetrain.set_speed_turn(0, dir * 50);

        // If we've been off track for too long, reverse direction
        if (millis() - m_offTrackInitTime > m_offTrackWaitTime)
        {
            dir *= -1;
            m_offTrackInitTime = millis();
            m_offTrackWaitTime *= 2;
        }
    }
    // If we're on track, follow the line
    else
    {
        // If we just got back on track, reset the wait time and turn off off track mode
        if (m_offTrackMode)
        {
            m_offTrackWaitTime = 100;
            m_offTrackMode = false;

            // Save the last working direction that got us back on track
            // This is an educated guess for the next time we go off track
            m_lastWorkingDir = dir;
        }

        // Set the speed and turn based on the PID controller
        struct MotorCommand speeds;
        speeds = m_drivetrain.compute_proportional(m_pidController, 15, get_left_IR_raw(), get_right_IR_raw());
        m_drivetrain.set_speed(speeds);
    }
}

void Robot::data_state_init()
{
    u08 left_ir_reading;
    u08 right_ir_reading;
    m_drivetrain.stop();

    while (!m_button.get() && m_num_data_pts < MAX_DATA_PTS)
    {
        /* code */
        _delay_ms(300);
        left_ir_reading = get_left_IR_raw();
        right_ir_reading = get_right_IR_raw();

        m_data_pts[m_num_data_pts] = {
            left_ir_reading,
            right_ir_reading,
            m_drivetrain.compute_proportional(m_pidController, 15, left_ir_reading, right_ir_reading)};

        m_num_data_pts++;

        clear_screen();
        print_string("Data");
        lcd_cursor(5, 0);
        print_num(m_num_data_pts);
        lcd_cursor(0, 1);
        print_num(left_ir_reading);
        lcd_cursor(4, 1);
        print_num(right_ir_reading);
    }
}

void Robot::data_state_periodic()
{
    struct MotorCommand speeds;
    speeds = m_drivetrain.compute_proportional(m_pidController, 15, get_left_IR_raw(), get_right_IR_raw());
    lcd_cursor(0, 1);
    print_num((u16)speeds.left_speed);
}

void Robot::print_controller_string()
{
    clear_screen();
    switch (m_controllerType)
    {
    case PID_MODE:
        print_string("Proportional");
        break;
    case DATA_MODE:
        print_string("Data");
        break;
    case TRAINING_MODE:
        print_string("Training");
        break;
    case NEURAL_NETWORK_MODE:
        print_string("Neural");
        break;
    default:
        break;
    }
}

void Robot::training_state_init() {}
void Robot::training_state_periodic() {}
void Robot::neural_state_init() {}
void Robot::neural_state_periodic() {}
