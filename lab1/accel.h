#include "globals.h"
#include <stdint.h>
#include <math.h>

#ifndef ACCEL_H
#define ACCEL_H

u08 get_accel_x_lsb();
u08 get_accel_y_lsb();
u08 get_accel_z_lsb();
u16 get_full_accel_x();
u16 get_full_accel_y();
u16 get_full_accel_z();
float raw_to_g(uint16_t raw);
float get_pitch_deg();
float get_roll_deg();

#endif
