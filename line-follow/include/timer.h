//Name:  Lorenzo Pedroza and Chris Lawson
//Lab  2
//Description: A timing library.
#include <Bumblebee.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#pragma once

extern volatile unsigned long timer1_millis;

void init_millis(unsigned long f_cpu);
unsigned long millis();
unsigned long secs();
