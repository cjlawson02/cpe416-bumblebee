// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 2
// Description: Drivetrain library to help run the differential drive.
#pragma once

#include "motor.h"
#include "pid_controller.h"
#include "light_sensor.h"

struct MotorCommand {   // Structure declaration
  float left_speed;          // Member (int variable)
  float right_speed;       
};

class Drivetrain
{
public:
    Drivetrain(const int left_motor, const int right_motor);

    void setup();
    void set_speed(const float left_speed, const float right_speed);
    void set_speed(const float speed);
    void set_speed_turn(const float speed, const float turn);
    struct MotorCommand Drivetrain::compute_proportional(PID pid, const float fwd_speed, const float left_ir_percent, const float right_ir_percent);

private:
    int m_leftMotor;
    int m_rightMotor;
};
