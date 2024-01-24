#include "light_sensor.h"

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
    return analog_to_percent(analog(ANALOG3_PIN));
}

float get_right_IR_amount()
{
    return analog_to_percent(analog(ANALOG2_PIN));
}
