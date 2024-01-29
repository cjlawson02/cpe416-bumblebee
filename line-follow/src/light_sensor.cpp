#include "light_sensor.h"

const int WHITE_VAL = 150;
const int DIFF = 70;

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
    return Util::bound((get_left_IR_amount() - WHITE_VAL) / DIFF, 0, 1);
}

float get_right_IR_percent()
{
    return Util::bound((get_right_IR_amount() - WHITE_VAL) / DIFF, 0, 1);
}

float get_IR_diff()
{
    return get_left_IR_percent() - get_right_IR_percent();
}
