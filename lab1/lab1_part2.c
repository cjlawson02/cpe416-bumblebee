/*
Name: Chris Lawson and Lorenzo Pedroza
Assignment: Lab 1 Part 2
Description: This program repeatedly scrolls our full names across the LCD display.
             Pressing the user button switches the lab partner name shown.
*/

#include "globals.h"
#include <util/delay.h>
#include <string.h>

// Initialize global constants for names
const char name1[] = "Chris Lawson";
const char name2[] = "Lorenzo Pedroza";
const uint8_t MAX_SCREEN_LEN = 8;
uint8_t btn_pressed = 0;

int main(void)
{
    init(); // initialize the board hardware
    clear_screen();

    char *name_to_display = name1;

    // Initialize variables
    while (1)
    {
        // Get the length of the string
        uint8_t len = strlen(name_to_display);

        // If the string is less than 8 characters, print it and return, otherwise scroll it and loop
        if (len <= MAX_SCREEN_LEN)
        {
            clear_screen();
            print_string(name_to_display);
            continue;
        }

        // Loop through the string, shifting it over one character each time
        for (uint8_t i = 0; i < strlen(name_to_display); i++)
        {
            // Print the string
            print_string(name_to_display + i);

            // Delay for 300ms
            _delay_ms(300);

            // Clear the screen
            clear_screen();

            // Check if the button is pressed
            if (get_btn() == 1)
            {
                // If this is the initial press, switch the name and set the flag
                if (btn_pressed == 0)
                {
                    if (name_to_display == name2)
                        name_to_display = name1;
                    else
                        name_to_display = name2;
                    btn_pressed = 1;
                    break;
                }
            }

            // If the button is no longer pressed, clear the flag
            else
            {
                btn_pressed = 0;
            }
        }
    }

    return 0;
}
