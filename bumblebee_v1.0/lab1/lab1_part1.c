/*
Name: Chris Lawson and Lorenzo Pedroza
Assignment: Lab 1 Part 1
Description: This program fades an LED on and off continuously
*/

#include "globals.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>


//Function by Lorenzo Pedroza
void var_delay_ms(double del_time) {
   double j = 0;
   for (j=0; j < del_time; j++)
      _delay_ms(1);
}

void var_delay_us(double del_time) {
   double j = 0;
   for (j=0; j < del_time; j++)
      _delay_us(1);
}


void fade_on(u08 led_pin) {
   double i;
   for(i=1000; i > 0; i-=50)
   {
      led_on(led_pin);
      var_delay_us(i);
      led_off(led_pin);
      var_delay_us(i);
   }
}

void time_on(u08 pin, const double time_ms, double duty_cycle_percent) {
   double i = 0; 
   for (i=0; i < time_ms; i++)
   {
      //for some odd reasons, I guess overhead from function calls, we can use assume the loop takes 10 ms instead
      led_on(pin);
      var_delay_us(duty_cycle_percent);
      led_off(pin);
      var_delay_us(100-duty_cycle_percent);
   }
   led_off(pin);
}

int main(void) {
   init();  //initialize the board hardware

   digital_dir(LED0_PIN, 1);
  
   int i = 0;
   while(1){
      for (i=0; i < 100; i++)
         time_on(LED0_PIN, 25, i);
      for (i=100; i > 0; i--)
         time_on(LED0_PIN, 25, i);
   }

   return 0;
}
