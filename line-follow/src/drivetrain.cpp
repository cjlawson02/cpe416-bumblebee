// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 2
// Description: Drivetrain library to help run the differential drive.
#include "drivetrain.h"

Drivetrain::Drivetrain(const int left_motor, const int right_motor) : m_leftMotor(left_motor), m_rightMotor(right_motor)
{
}

void Drivetrain::setup()
{
    set_speed(0);
}

void Drivetrain::set_speed(const float left_speed, const float right_speed)
{
    motor(this->m_leftMotor, left_speed);
    motor(this->m_rightMotor, -right_speed);
}

void Drivetrain::set_speed(const float speed)
{
    set_speed(speed, speed);
}

void Drivetrain::set_speed_turn(const float speed, const float turn)
{
    set_speed(speed + turn, speed - turn);
}
