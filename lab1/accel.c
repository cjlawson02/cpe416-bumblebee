#include "accel.h"

u08 get_accel_x_lsb()
{
    return i2c_regread(MMA8453_ADDR, 0x2);
}

u08 get_accel_y_lsb()
{
    return i2c_regread(MMA8453_ADDR, 0x4);
}

u08 get_accel_z_lsb()
{
    return i2c_regread(MMA8453_ADDR, 0x6);
}

u16 get_full_accel_x()
{
    u08 msb = get_accel_x();
    u08 lsb = get_accel_x_lsb();
    return (msb << 2) | (lsb & 0x03);
}

u16 get_full_accel_y()
{
    u08 msb = get_accel_y();
    u08 lsb = get_accel_y_lsb();
    return (msb << 2) | (lsb & 0x03);
}

u16 get_full_accel_z()
{
    u08 msb = get_accel_z();
    u08 lsb = get_accel_z_lsb();
    return (msb << 2) | (lsb & 0x03);
}

float raw_to_g(uint16_t raw)
{
    // Convert raw data from 2's complement to signed integer
    int16_t signedData = raw > 511 ? raw - 1024 : raw;
    return signedData / 256.0f;
}

float get_pitch_deg()
{
    float x = raw_to_g(get_accel_x());
    float y = raw_to_g(get_accel_y());
    float z = raw_to_g(get_accel_z());
    return atan2(x, sqrt(y * y + z * z)) * 180.0f / M_PI;
}

float get_roll_deg()
{
    float y = raw_to_g(get_accel_y());
    float z = raw_to_g(get_accel_z());
    return atan2(y, z) * 180.0f / M_PI;
}
