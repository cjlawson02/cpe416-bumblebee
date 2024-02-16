// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 2
// Description: The main file for running all parts of program 2.
#include "main.h"

#define P 12.0
#define I 0.0
#define D 1.0

int main()
{
  Robot robot = Robot();
  robot.setup();
  robot.run();

  return 0;
}
