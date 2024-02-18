#pragma once

#include <Bumblebee.h>

struct MotorCommand
{                     // Structure declaration
    float left_speed; // Member (int variable)
    float right_speed;
};

struct TrainingData
{ // Structure declaration
    u08 left_ir_reading;
    u08 right_ir_reading;
    MotorCommand speeds;
};
