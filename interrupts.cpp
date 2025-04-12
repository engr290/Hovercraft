


#include "globals.h"

volatile unsigned long system_time = 0;
volatile bool top_ir_triggered = false;

ISR(TIMER2_COMPA_vect) {
	system_time++;  // Increment timer count each time the interrupt is triggered
}


// Interrupt Service Routine
ISR(INT0_vect) {
  top_ir_triggered = true;
}