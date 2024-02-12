// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 2
// Description: Drivetrain library to help run the differential drive.
#pragma once

#include "motor.h"

class Drivetrain
{
public:
    Drivetrain(const int left_motor, const int right_motor);

    void setup();
    void set_speed(const float left_speed, const float right_speed);
    void set_speed(const float speed);
    void set_speed_turn(const float speed, const float turn);

private:
    int m_leftMotor;
    int m_rightMotor;
};
