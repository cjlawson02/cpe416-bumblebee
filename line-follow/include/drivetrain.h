// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 2
// Description: Drivetrain library to help run the differential drive.
#pragma once

#include "motor.h"
#include "pid_controller.h"
#include "light_sensor.h"
#include "neural_network.h"

struct MotorCommand
{                   // Structure declaration
  float left_speed; // Member (int variable)
  float right_speed;
};

class Drivetrain
{
public:
  Drivetrain(const int left_motor, const int right_motor);

  void setup();
  void set_speed(const float left_speed, const float right_speed);
  void set_speed(MotorCommand m_command);
  void set_speed(const float speed);
  void set_speed_turn(const float speed, const float turn);
  void stop();
  struct MotorCommand compute_proportional(PID *pid, const float fwd_speed, u08 left_ir_reading, u08 right_ir_reading);
  struct MotorCommand compute_neural_network(NeuralNetwork *nn, const std::vector<float> inputs);

private:
  int m_leftMotor;
  int m_rightMotor;
};
