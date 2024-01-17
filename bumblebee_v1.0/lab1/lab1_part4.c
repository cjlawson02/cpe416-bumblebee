/*
Name: Chris Lawson and Lorenzo Pedroza
Assignment: Lab 1 Part 2
Description: This program repeatedly scrolls our full names across the LCD display.
             Pressing the user button should switches between lab partners.
*/

#include "globals.h"
#include <util/delay.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Function by Chris Lawson

// Initialize global constants for names
const uint8_t MAX_SCREEN_LEN = 8;

double convert_acceleration(uint8_t acceleration)
{
    if (acceleration > 127)
    {
        return -((255.0 - acceleration) / 127.0);
    }
    else
    {
        return (acceleration / 128.0);
    }
}

double get_normalized_accel_x()
{
    return convert_acceleration(get_accel_x());
}

double get_normalized_accel_y()
{
    return convert_acceleration(get_accel_y());
}

double get_normalized_accel_z()
{
    return convert_acceleration(get_accel_z());
}

double get_pitch()
{
    double x = get_normalized_accel_x();
    double y = get_normalized_accel_y();
    double z = get_normalized_accel_z();
    return atan2(x, sqrt(y * y + z * z));
}
double get_roll()
{
    double x = get_normalized_accel_x();
    double y = get_normalized_accel_y();
    double z = get_normalized_accel_z();
    return atan2(y, sqrt(x * x + z * z));
}

void doubleToString(char *str, const double value, const int precision)
{
    int intPart = (int)value;
    int fracPart = (int)((value - (double)intPart) * pow(10, precision));
    sprintf(str, "%d.%d", intPart, abs(fracPart));
}

int main(void)
{
    init(); // initialize the board hardware
    clear_screen();

    const char *text = "416"; // Text to display
    int textLen = strlen(text);

    // Cursor positions for scrolling
    int cursorPos = MAX_SCREEN_LEN - textLen; // Start from the rightmost position
    int line = 0;                             // Start line (top)

    while (1)
    {
        double pitch = get_pitch(); // Get current pitch value
        double roll = get_roll();   // Get current roll value

        // Adjust cursor position based on roll
        if (roll > 0 && cursorPos < MAX_SCREEN_LEN - 1)
        {
            cursorPos++;
        }
        else if (roll < 0 && cursorPos > 0)
        {
            cursorPos--;
        }

        // Adjust line based on pitch
        line = (pitch > 0) ? 1 : 0;

        clear_screen();           // Clear the screen
        lcd_cursor(0, cursorPos); // Set the cursor position
        print_string(text);       // Print the text at the new cursor position

        _delay_ms(100); // Delay for 100ms
    }
}
