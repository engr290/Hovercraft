


#include "globals.h"

volatile unsigned long system_time = 0;

ISR(TIMER2_COMPA_vect) {
	system_time++;  // Increment timer count each time the interrupt is triggered
}
