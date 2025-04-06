
#ifndef PERIPHERALS_H
#define PERIPHERALS_H 

#include "globals.h"
#include "i2c.h"

// Servo
void init_timer_0();  // PD5 and PD6 output
void init_timer_1();  // PB1 and PB2 output
void init_timer_2();  // general timer

void set_servo_A(int16_t degrees);  // OCR1A : PB1
void set_servo_B(int16_t degrees);  // OCR1B : PB2

void set_fan_A(uint8_t power);  // OCR0B : PD5
void set_fan_B(uint8_t power);  // OCR0A : PD6

void init_lift();
void set_lift(bool on); // PD7

// i2c
void init_imu();
void get_imu_data();

void c_delay(uint32_t ms);

#endif