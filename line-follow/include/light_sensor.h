// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 2 Part 2 and 3
// Description: Light sensor helper library for Lab 2 parts 2 and 3
#pragma once

#include <Bumblebee.h>
#include "util.h"
#include "calibration_data.h"

float analog_to_percent(u08 analog_value);

float get_left_light_amount();
float get_right_light_amount();
u08 get_left_IR_raw();
u08 get_right_IR_raw();
float get_IR_amount(u08 raw_reading);
float get_left_IR_amount(u08 left_reading_raw);
float get_right_IR_amount(u08 right_reading_raw);
float get_left_IR_amount();
float get_left_IR_percent(float left_IR_amount);
float get_right_IR_percent(float right_IR_amount);
float get_right_IR_amount();
float get_left_IR_percent();
float get_right_IR_percent();
float get_IR_diff();
float get_IR_diff(u08 analog_left_ir, u08 analog_right_ir);
float get_IR_diff(float left_IR_percent, float right_IR_percent);
bool off_track();
