/*
Name: Chris Lawson and Lorenzo Pedroza
Assignment: Lab 1 Part 2
Description: This program repeatedly scrolls our full names across the LCD display.
             Pressing the user button should switches between lab partners.
*/

#include "globals.h"
#include <util/delay.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

// Function by Chris Lawson

// Initialize global constants for names
const uint8_t MAX_SCREEN_LEN = 8;
volatile uint8_t btn_pressed = 0;

float get_pitch()
{
    return atan2(get_accel_x(), sqrt(get_accel_y() * get_accel_y() + get_accel_z() * get_accel_z()));
}
float get_roll()
{
    return atan2(get_accel_y(), sqrt(get_accel_x() * get_accel_x() + get_accel_z() * get_accel_z()));
}

int main(void)
{
    init(); // initialize the board hardware
    clear_screen();

    while (1)
    {
        clear_screen();

        // Delay for 300ms
        _delay_ms(300);
    }
    return 0;
}
