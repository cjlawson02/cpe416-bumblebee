#include "main.h"

Drivetrain drivetrain = Drivetrain(SERVO0_PIN, SERVO1_PIN);

int main()
{
  setup();

  // lab2_part1();
  // lab2_part2();
  // lab2_part3();
  lab2_part4();
  return 0;
}

void setup()
{
  drivetrain.setup();
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
      drivetrain.set_speed(i);
      _delay_ms(50);
    }

    // gradually slows the motors to a stop
    for (int i = 100; i >= 0; i--)
    {
      print_speed(i);
      drivetrain.set_speed(i);
      _delay_ms(50);
    }

    // gradually spins the motors to full speed backward
    for (int i = 0; i >= -100; i--)
    {
      print_speed(i);
      drivetrain.set_speed(i);
      _delay_ms(50);
    }

    // gradually slows the motors to a stop
    for (int i = -100; i <= 0; i++)
    {
      print_speed(i);
      drivetrain.set_speed(i);
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
        drivetrain.set_speed(-pow(get_left_light_amount(), 3) * 1000, -pow(get_right_light_amount(), 3) * 1000);
        _delay_ms(20);
      }
      else
      {
        drivetrain.set_speed(100);
      }
    }
    else
    {
      print_string("2b");
      if (get_right_light_amount() > 0.5 || get_left_light_amount() > 0.5)
      {
        drivetrain.set_speed(-pow(get_right_light_amount(), 3) * 100, -pow(get_left_light_amount(), 3) * 100);
      }
      else
      {
        drivetrain.set_speed(100);
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
        drivetrain.set_speed(100);
      }
    }
    else
    {
      print_string("Vehicle 3b");
      if (get_right_light_amount() > 0.5 || get_left_light_amount() > 0.5)
      {
        drivetrain.set_speed(pow(1 - get_right_light_amount(), 3) * 100, pow(1 - get_left_light_amount(), 3) * 100);
      }
      else
      {
        drivetrain.set_speed(100);
      }
    }
  }
}

void lab2_part4()
{
  // Line follower with PID
  PID pid = PID(17.0, 2.0, 5.0);
  pid.setBounds(-100, 100);

  while (1)
  {
    print_num(get_left_IR_amount());
    _delay_ms(20);
    clear_screen();

    // Set the motors
    drivetrain.set_speed_turn(15, -pid.calcOutputWithError(get_IR_diff()));
  }
}
