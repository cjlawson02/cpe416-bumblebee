// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 2 Part 2 and 3
// Description: Light sensor helper library for Lab 2 parts 2 and 3
#pragma once

#include <Bumblebee.h>
#include "util.h"

float analog_to_percent(u08 analog_value);

float get_left_light_amount();
float get_right_light_amount();
float get_left_IR_amount();
float get_right_IR_amount();
float get_left_IR_percent();
float get_right_IR_percent();
float get_IR_diff();
float get_IR_diff(const float left_ir_pecent, const float right_ir_percent);
bool off_track();
