//Name:  Lorenzo Pedroza and Chris Lawson
//Lab 2 Part 2 and 3
//Description: Light sensor helper library for Lab 2 parts 2 and 3
#include "light_sensor.h"

const int LEFT_WHITE_VAL = 110;
const int LEFT_BLACK_VAL = 180;
const int RIGHT_WHITE_VAL = 185;
const int RIGHT_BLACK_VAL = 220;
const int LEFT_DIFF = LEFT_BLACK_VAL - LEFT_WHITE_VAL;
const int RIGHT_DIFF = RIGHT_BLACK_VAL - RIGHT_WHITE_VAL;
const float PERCENT_THRESHOLD = 0.5;

float analog_to_percent(u08 analog_value)
{
    return (float)analog_value / 255.0;
}

float get_left_light_amount()
{
    return analog_to_percent(analog(ANALOG0_PIN));
}

float get_right_light_amount()
{
    return analog_to_percent(analog(ANALOG1_PIN));
}

u08 get_left_IR_raw()
{
    return analog(ANALOG3_PIN);
}

u08 get_right_IR_raw()
{
    return analog(ANALOG2_PIN);
}


float get_IR_amount(u08 raw_reading)
{
    return (float)raw_reading;
}

float get_left_IR_amount(u08 left_reading_raw)
{
    return get_IR_amount(get_left_IR_raw());
}

float get_right_IR_amount(u08 right_reading_raw)
{
    return get_IR_amount(get_right_IR_raw());
}

float get_left_IR_amount()
{
    return get_IR_amount(get_left_IR_raw());//analog(ANALOG3_PIN);
}

float get_right_IR_amount()
{
    return get_IR_amount(get_right_IR_raw());//analog(ANALOG2_PIN);
}

float get_left_IR_percent(float left_IR_amount)
{
    return Util::bound((left_IR_amount - LEFT_WHITE_VAL) / LEFT_DIFF, 0, 1);
}

float get_right_IR_percent(float right_IR_amount)
{
    return Util::bound((right_IR_amount - RIGHT_WHITE_VAL) / RIGHT_DIFF, 0, 1);
}

float get_left_IR_percent()
{
    return get_left_IR_percent(get_left_IR_amount());
}

float get_right_IR_percent()
{
    return get_right_IR_percent(get_right_IR_amount());
}

float get_IR_diff(float left_IR_percent, float right_IR_percent)
{
    return left_IR_percent-right_IR_percent;
}

float get_IR_diff()
{
    return get_IR_diff(get_left_IR_percent(), get_right_IR_percent());
}

float get_IR_diff(u08 analog_left_ir, u08 analog_right_ir)
{
    return get_IR_diff(get_left_IR_percent(get_left_IR_amount(analog_left_ir)), get_right_IR_percent(get_right_IR_amount(analog_right_ir)));
}

bool off_track()
{
    return (get_left_IR_percent() < PERCENT_THRESHOLD) && (get_right_IR_percent() < PERCENT_THRESHOLD);
}
