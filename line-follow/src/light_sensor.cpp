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

float get_left_IR_amount()
{
    return analog(ANALOG3_PIN);
}

float get_right_IR_amount()
{
    return analog(ANALOG2_PIN);
}

float get_left_IR_percent()
{
    return Util::bound((get_left_IR_amount() - LEFT_WHITE_VAL) / LEFT_DIFF, 0, 1);
}

float get_right_IR_percent()
{
    return Util::bound((get_right_IR_amount() - RIGHT_WHITE_VAL) / RIGHT_DIFF, 0, 1);
}

float get_IR_diff()
{
    return get_left_IR_percent() - get_right_IR_percent();
}

bool off_track()
{
    return (get_left_IR_percent() < PERCENT_THRESHOLD) && (get_right_IR_percent() < PERCENT_THRESHOLD);
}
