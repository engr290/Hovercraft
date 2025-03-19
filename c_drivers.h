
#ifndef C_DRIVERS_H_
#define C_DRIVERS_H_

#include "globals.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>


// TODO
void c_init_timer2(); // TODO
void c_delay_milli(unsigned long ms);
uint64_t c_current_time(); // return current time milli sec


void init_gpio_pins(); // TODO


// ADC
bool c_set_adc_reference(c_ADC_ref reference);
bool c_set_adc_pin(uint8_t pin);
uint16_t c_analog_read();

// i2c drivers
void c_i2c_init();
void c_i2c_start();
void c_i2c_stop();
void c_i2c_write(uint8_t data);
uint8_t c_i2c_read_ack();
uint8_t c_i2c_read_nack();


#endif