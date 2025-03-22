
#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <avr/io.h>
#include <avr/interrupt.h>


typedef enum {
	c_VCC,
	c_AREF,
	c_internal_1_1
} c_ADC_ref;


#define F_CPU 16000000UL

// IMU
#define IMU_ADDR  0x68  		// 7 bit address
#define IMU_WHO_AM_I 0x0
#define IMU_PWR_REG 0x6B
#define IMU_X_ACCEL_REG 0x3B 	// It is the x acceleration and rest of the registers are increamentally after it
#define IMU_GYTO_X 0x43
#define DEAD_ZONE 1.0
#define Gravity 9.80665
#define ACCEL_SCALE 16384.0  	// ±2g range
#define GYRO_SCALE 131.0     	// ±250/s range

// TODO
// Find the exact numbers
#define WIDTH 52	//50-55cm so I chosen the average
#define LENGTH 235	// in cm
#define TURN 3		

extern float imu_data[12];
extern float system_data[9];
extern unsigned long timer_count;
extern bool servo_mode;

enum HovercraftStates{
	Init,
	Forward,
	UTurn,
	Recovery,
	Adjust,
	TurnOff
} system_state;


#endif