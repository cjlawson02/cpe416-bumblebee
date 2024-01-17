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

    char text[] = "416";

    int i = 0;
    int row = 0;
    int col = 0;
    char displayString[MAX_SCREEN_LEN + 1];
    strncpy(displayString, text, MAX_SCREEN_LEN);

    while (1)
    {
        float roll = get_roll_deg();   // Get current roll value
        float pitch = get_pitch_deg(); // Get current pitch value

        clear_screen();

        // If rolling, scroll to the right/left
        if (abs(roll) > 5)
        {
            if (roll > 0)
            {
                // Tilting to the left
                if (col > 1)
                {
                    strncpy(displayString, text, MAX_SCREEN_LEN);
                    col--;
                    i = 0;
                }
                else if (i < strlen(text))
                {
                    strncpy(displayString, text + i, MAX_SCREEN_LEN);
                    i++;
                    col = 0;
                }
            }
            else
            {
                // Tilting to the right

                if (i > 0)
                {
                    i--;
                    strncpy(displayString, text + i, MAX_SCREEN_LEN);
                    col = 0;
                }
                else if (col < MAX_SCREEN_LEN - 1)
                {
                    strncpy(displayString, text, MAX_SCREEN_LEN);
                    col++;
                    i = 0;
                }
            }
        }

        if (abs(pitch) > 5)
        {
            row = (pitch > 0) ? 0 : 1;
        }

        lcd_cursor(col, row);
        print_string(displayString);

        _delay_ms(200); // Delay for 500ms
    }
}
