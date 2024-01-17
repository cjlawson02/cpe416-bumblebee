/*
Name: Chris Lawson and Lorenzo Pedroza
Assignment: Lab 1 Part 2
Description: This program repeatedly scrolls our full names across the LCD display.
             Pressing the user button should switches between lab partners.
*/

#include "globals.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function by Chris Lawson

// Initialize global constants for names
const uint8_t MAX_SCREEN_LEN = 8;

void floatToString(char *str, const float value, const int precision)
{
    int intPart = (int)value;
    int fracPart = (int)((value - (float)intPart) * pow(10, precision));
    sprintf(str, "%d.%d", intPart, abs(fracPart));
}

int main(void)
{
    init(); // initialize the board hardware
    clear_screen();

    const char text[] = "416";
    const char ext[] = "16";
    const char xt[] = "6";
    int textLen = strlen(text);

    // Cursor positions for scrolling
    int cursorPos = MAX_SCREEN_LEN - textLen; // Start from the rightmost position
    int line = 0;                             // Start line (top)

    while (1)
    {
        float pitch = get_pitch_deg(); // Get current pitch value
        float roll = get_roll_deg();   // Get current roll value

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

        clear_screen();              // Clear the screen
        lcd_cursor(line, cursorPos); // Set the cursor position
        print_string(text);          // Print the text at the new cursor position

        _delay_ms(500); // Delay for 500ms
    }
}
