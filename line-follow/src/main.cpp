#include "main.h"

int main()
{
  setup();

  // lab2_part1();
  lab2_part2();
  // lab2_part3();
  // lab2_part4();
  return 0;
}

void setup()
{
  init_millis(16000000UL);
  init();
  motor(SERVO0_PIN, 0);
  motor(SERVO1_PIN, 0);
}

void print_speed(int speed)
{
  clear_screen();
  if (speed < 0)
  {
    print_string("-");
  }
  print_num(abs(speed));
}

void lab2_part1()
{
  while (1)
  {
    // gradually spins the motors to full speed forward
    for (int i = 0; i <= 100; i++)
    {
      print_speed(i);
      motor(SERVO0_PIN, i);
      motor(SERVO1_PIN, -i);
      _delay_ms(50);
    }

    // gradually slows the motors to a stop
    for (int i = 100; i >= 0; i--)
    {
      print_speed(i);
      motor(SERVO0_PIN, i);
      motor(SERVO1_PIN, -i);
      _delay_ms(50);
    }

    // gradually spins the motors to full speed backward
    for (int i = 0; i >= -100; i--)
    {
      print_speed(i);
      motor(SERVO0_PIN, i);
      motor(SERVO1_PIN, -i);
      _delay_ms(50);
    }

    // gradually slows the motors to a stop
    for (int i = -100; i <= 0; i++)
    {
      print_speed(i);
      motor(SERVO0_PIN, i);
      motor(SERVO1_PIN, -i);
      _delay_ms(50);
    }
  }
}

void lab2_part2()
{
  bool button_pressed = false;

  // true = vehicle 2a, false = vehicle 2b
  bool vehicle_mode = true;

  while (1)
  {
    // Handle switching modes
    if (get_btn())
    {
      if (!button_pressed)
      {
        clear_screen();
        button_pressed = true;
        vehicle_mode = !vehicle_mode;
      }
    }
    else
    {
      button_pressed = false;
    }

    // clear_screen();
    // print_num(get_right_light_amount() * 100);
    // _delay_ms(1000);

    // Handle mode logic
    if (vehicle_mode)
    {
      // Fear
      if (get_right_light_amount() > 0.8 || get_left_light_amount() > 0.8)
      {
        motor(SERVO0_PIN, -pow(get_left_light_amount(), 3) * 1000);
        motor(SERVO1_PIN, pow(get_right_light_amount(), 3) * 1000);
        _delay_ms(20);
      }
      else
      {
        motor(SERVO0_PIN, 100);
        motor(SERVO1_PIN, -100);
      }
    }
    else
    {
      print_string("2b");
      if (get_right_light_amount() > 0.5 || get_left_light_amount() > 0.5)
      {
        motor(SERVO0_PIN, -pow(get_right_light_amount(), 3) * 100);
        motor(SERVO1_PIN, pow(get_left_light_amount(), 3) * 100);
      }
      else
      {
        motor(SERVO0_PIN, 100);
        motor(SERVO1_PIN, -100);
      }
    }
  }
}

void lab2_part3()
{
  bool button_pressed = false;

  // true = vehicle 3a, false = vehicle 3b
  bool vehicle_mode = true;

  while (1)
  {
    // Handle switching modes
    if (get_btn())
    {
      if (!button_pressed)
      {
        button_pressed = true;
        vehicle_mode = !vehicle_mode;
      }
    }
    else
    {
      button_pressed = false;
    }

    // Handle mode logic
    clear_screen();
    if (vehicle_mode)
    {
      print_string("Vehicle 3a");
      // Fear
      if (get_right_light_amount() > 0.5 || get_left_light_amount() > 0.5)
      {
        motor(SERVO0_PIN, pow(1 - get_left_light_amount(), 3) * 100);
        motor(SERVO1_PIN, -pow(1 - get_right_light_amount(), 3) * 100);
      }
      else
      {
        motor(SERVO0_PIN, 100);
        motor(SERVO1_PIN, -100);
      }
    }
    else
    {
      print_string("Vehicle 3b");
      if (get_right_light_amount() > 0.5 || get_left_light_amount() > 0.5)
      {
        motor(SERVO0_PIN, pow(1 - get_right_light_amount(), 3) * 100);
        motor(SERVO1_PIN, -pow(1 - get_left_light_amount(), 3) * 100);
      }
      else
      {
        motor(SERVO0_PIN, 100);
        motor(SERVO1_PIN, -100);
      }
    }
  }
}

void lab2_part4()
{
  // Line follower with PID
  PID pid = PID(0.5, 0, 0);

  while (1)
  {
    // Calculate the error
    double error = get_left_IR_amount() - get_right_IR_amount();

    // Calculate the output
    double output = pid.calcOutputWithError(error);

    // Set the motors
    motor(SERVO0_PIN, output * 100);
    motor(SERVO1_PIN, -output * 100);
  }
}
