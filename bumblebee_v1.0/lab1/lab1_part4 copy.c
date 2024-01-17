// /*
// Name: Chris Lawson and Lorenzo Pedroza
// Assignment: Lab 1 Part 2
// Description: This program repeatedly scrolls our full names across the LCD display.
//              Pressing the user button should switches between lab partners.
// */

// #include "globals.h"
// #include <util/delay.h>
// #include <math.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// // Function by Chris Lawson

// // Initialize global constants for names
// const uint8_t MAX_SCREEN_LEN = 8;

// double convert_acceleration(uint8_t acceleration)
// {
//     if (acceleration > 127)
//     {
//         return -((255.0 - acceleration) / 127.0);
//     }
//     else
//     {
//         return (acceleration / 128.0);
//     }
// }

// double get_normalized_accel_x()
// {
//     return convert_acceleration(get_accel_x());
// }

// double get_normalized_accel_y()
// {
//     return convert_acceleration(get_accel_y());
// }

// double get_normalized_accel_z()
// {
//     return convert_acceleration(get_accel_z());
// }

// double get_pitch()
// {
//     double x = get_normalized_accel_x();
//     double y = get_normalized_accel_y();
//     double z = get_normalized_accel_z();
//     return atan2(x, sqrt(y * y + z * z));
// }
// double get_roll()
// {
//     double x = get_normalized_accel_x();
//     double y = get_normalized_accel_y();
//     double z = get_normalized_accel_z();
//     return atan2(y, sqrt(x * x + z * z));
// }

// void doubleToString(char *str, const double value, const int precision)
// {
//     int intPart = (int)value;
//     int fracPart = (int)((value - (double)intPart) * pow(10, precision));
//     sprintf(str, "%d.%d", intPart, abs(fracPart));
// }

// int main(void)
// {
//     init(); // initialize the board hardware
//     clear_screen();

//     const char *text = "416"; // Text to display
//     int textLen = strlen(text);

//     // Cursor positions for scrolling
//     int cursorPos = MAX_SCREEN_LEN - textLen; // Start from the rightmost position
//     int line = 0;                             // Start line (top)

//     while (1)
//     {
//         double pitch = get_pitch(); // Get current pitch value
//         double roll = get_roll();   // Get current roll value

//         // Adjust cursor position based on roll
//         if (roll > 0 && cursorPos < MAX_SCREEN_LEN - 1)
//         {
//             cursorPos++;
//         }
//         else if (roll < 0 && cursorPos > 0)
//         {
//             cursorPos--;
//         }

//         // Adjust line based on pitch
//         line = (pitch > 0) ? 1 : 0;

//         clear_screen();           // Clear the screen
//         // lcd_cursor(line, cursorPos); // Set the cursor position
//         // print_string(text);       // Print the text at the new cursor position

//         char str[8];
//         doubleToString(str, get_normalized_accel_x(), 2);
//         print_string(str);
//         _delay_ms(100); // Delay for 100ms
//     }
// }

/*
Name: Ahren Dosanjh and Lorenzo Pedroza
Assignment: Lab 1 Part 4
Description: This program prints our names on the LCD screen and uses the accelerometer to scroll them
             across the screen.
*/

#include "globals.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <string.h>

#define MAX_i 7
#define MIN_i 0

#define MAX_j 1
#define MIN_j 0

int main(void)
{
    init(); // initialize board hardware

    char name[] = "416"; // name to print
    char ame[] = "16";   // name to print
    char me[] = "6";     // name to prin
    lcd_cursor(2, 0);    // set cursor to first row
    print_string(name);  // print name

    int8_t i = 2; // counter for x axis
    int8_t j = 0; // counter for y axis
    int8_t l = 0; // counter for y axis
    int8_t k = 0; // counter for l

    u08 x, y;

    while (1)
    {
        x = get_accel_x(); // get x axis value
        y = get_accel_y(); // get y axis value

        clear_screen();

        char *str;

        if ((100 < y) && (y < 200) && i < MAX_i)
        {
            i++;
            l++;
            if (k != -1)
            {
                str = name; // print name
            }
            else
            {
                k++;
                str = ame; // print ame
            }
        }
        else if ((40 < y) && (y < 80) && i > MIN_i)
        {
            i--;
            l--;
            str = name; // print name
        }
        else if ((40 < y) && (y < 80) && l <= 0)
        {
            i = 0;
            if (k == 0)
            {
                str = ame; // print name
                k--;
            }
            else
            {
                str = me; // print name
            }
            l--;
        }
        if ((185 < x) && (x < 240) && j < MAX_j)
        {
            j++;
            str = name; // print name
        }
        else if ((30 < x) && (x < 60) && j > MIN_j)
        {
            j--;
        }

        lcd_cursor(i, j);   // set cursor to first row
        print_string(str); // print name

        _delay_ms(150); // delay 1 seconds
    }

    return 0;
}
