// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 2
// Description: Motor library to map the servo ranges to -100 (full reverse) to 100 (full forward).

#include "motor.h"

/**
 * Sets the speed of the desired motor.
 * @param num The motor number to set the speed of.
 * @param speed The speed to set the motor to, between -100 and 100.
 */
void motor(const u08 num, const int8_t speed)
{
    const int8_t bounded_speed = Util::bound(speed, -100, 100);

    // This function should call set_servo to spin the motor
    // A call to set_servo with position of 127 should stop the motor.  If your motor spins, you can calibrate your motors by adjusting the servo potentiometer with a screwdriver.

    set_servo(num, bounded_speed + 127);
}
