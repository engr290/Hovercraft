
#ifndef I2C_H
#define I2C_H

#include "globals.h"

// This section is only used for IMU
// i2c drivers
void c_i2c_init();
void c_i2c_start();
void c_i2c_stop();
void c_i2c_write(uint8_t data);
uint8_t c_i2c_read_ack();
uint8_t c_i2c_read_nack();


#endif