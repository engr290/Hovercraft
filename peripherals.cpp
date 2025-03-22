
#include "peripherals.h"
//---------------------------------------------------------------------------
//----------------------------------Servos-----------------------------------
//---------------------------------------------------------------------------

bool servo_mode = true;


//Angle of the servos from 0 to 180.
void init_servo_0() {
    DDRD |= (1 << PD6);  // Set PD6 (OC0A) as output for PWM
    TCCR0A = (1 << WGM00) | (1 << COM0A1); // Fast PWM, non-inverting mode, timer 0
    TCCR0B = (1 << WGM02) | (1 << CS01);   // Prescaler = 8
    OCR0A = 127;  // Set the pulse width for Servo 0 (middle position) - 0 to 255
}

void init_servo_1() {
    DDRB |= (1 << PB1); // Set PB1 (OC1A) as output for PWM
    TCCR1A = (1 << WGM11) | (1 << COM1A1); // Fast PWM, non-inverting mode, timer 1
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler = 8
    ICR1 = 39999; // Set TOP for 50Hz PWM frequency
    OCR1A = 3000; // // Set the pulse width for Servo 1 (middle position) - 0 to 39999
}


void set_servo_0(uint16_t angle) {
  // Clamp angle from 0 to 180
    if (angle > 180) angle = 180;
    if (angle < 0) angle = 0;
  
    //Pulse width calculation - from 600 to 2400
    uint16_t pulseWidth = ((uint32_t)angle * (2400 - 600) / 180) + 600;

    // Convert pulse width to timer counts (each count is 0.5µs with prescaler of 8)
    OCR0A = pulseWidth / 10; // Set the timer compare value - from 60 to 240
}

void set_servo_1(uint16_t angle) {
    // Clamp angle from 0 to 180
    if (angle > 180) angle = 180;
    if (angle < 0) angle = 0;
  
    //Pulse width calculation - from 600 to 2400
    uint16_t pulseWidth = ((uint32_t)angle * (2400 - 600) / 180) + 600;
  
    // Convert pulse width to timer counts (each count is 0.5µs with prescaler of 8)
    OCR1A = pulseWidth * 2; // Set the timer compare value - from 1200 to 4800
}

//---------------------------------------------------------------------------
//----------------------------------Fans-----------------------------------
//---------------------------------------------------------------------------











