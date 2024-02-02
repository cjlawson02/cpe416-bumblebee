//Name:  Lorenzo Pedroza and Chris Lawson
//Lab 2
//Description: Motor library to map the servo ranges to -100 (full reverse) to 100 (full forward).
#include <Bumblebee.h>
#include <stdlib.h>
#include "util.h"

#pragma once

void motor(const u08 num, const int8_t speed);
