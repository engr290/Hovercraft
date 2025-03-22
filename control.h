
#ifndef CONTROL_H
#define CONTROL_H

#include "peripherals.h"


void init_hovercraft();
void move_forward();
void angle_adjust(int16_t angle);
void turn_off();
void stop(uint8_t distance);


#endif