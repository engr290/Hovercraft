
#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>


// typedef enum {
// 	c_VCC,
// 	c_AREF,
// 	c_internal_1_1
// } c_ADC_ref;


// #define F_CPU 16000000UL


// Global variables
extern float imu_data[12];
extern float yaw_angle;
extern volatile unsigned long system_time;

// IMU
#define IMU_ADDR  0x68  // 7 bit address
#define IMU_WHO_AM_I 0x0
#define IMU_PWR_REG 0x6B
#define IMU_X_ACCEL_REG 0x3B // It is the x acceleration and rest of the registers are increamentally after it
#define IMU_GYTO_X 0x43
#define IMU_250 0x00
#define DEAD_ZONE_GYRO 1.0
#define DEAD_ZONE_ACCEL 0.1
#define Gravity 980.665
#define ACCEL_SCALE 16384.0  // ±2g range
#define GYRO_SCALE 131.0     // ±250°/s range

#endif