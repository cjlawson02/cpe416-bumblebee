//Name:  Lorenzo Pedroza and Chris Lawson
//Lab 2
//Description: Drivetrain library to help run the differential drive.
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
    float left_speed;
    float right_speed;
    int left_motor;
    int right_motor;
};
