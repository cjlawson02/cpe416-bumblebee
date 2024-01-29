#include "drivetrain.h"

Drivetrain::Drivetrain(const int left_motor, const int right_motor)
{
    this->left_motor = left_motor;
    this->right_motor = right_motor;
}

void Drivetrain::set_speed(const float left_speed, const float right_speed)
{
    motor(this->left_motor, left_speed);
    motor(this->right_motor, -right_speed);
}

void Drivetrain::set_speed(const float speed)
{
    set_speed(speed, speed);
}

void Drivetrain::set_speed_turn(const float speed, const float turn)
{
    set_speed(speed + turn, speed - turn);
}
