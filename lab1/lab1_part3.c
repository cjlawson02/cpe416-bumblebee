/*
Name: Chris Lawson and Lorenzo Pedroza
Assignment: Lab 1 Part 3
Description: This program implements a game of pong
             The user hits with the built in button.
*/

#include "globals.h"
#include <util/delay.h>

void var_delay_ms(double del_time)
{
   double j = 0;
   for (j = 0; j < del_time; j++)
      _delay_ms(1);
}

int main(void)
{
   init(); // initialize board hardware

   int i = 0;
   // initialize LED's 2-6 as output
   for (i = 2; i <= 6; i++)
      digital_dir(i, 1);

   for (i = 2; i <= 6; i++)
      digital_out(i, 0);

   double led_delay_ms = 1000;

   while (led_delay_ms) // while greater than 0
   {
      for (i = 2; i <= 6; i++)
      {
         digital_out(i, 1);
         var_delay_ms(led_delay_ms);

         if (!get_btn() && (i == 6)) // button not pressed (still high)
         {
            print_num(led_delay_ms);
            print_string(" ms");
            return 0; // end
         }

         // turn off last led
         digital_out(i, 0);
      }
      led_delay_ms -= 50;
   }
   return 0;
}
