
#include "globals.h"

ISR(TIMER2_COMPA_vect) {
	timer_count++;  // Increment timer count each time the interrupt is triggered
}