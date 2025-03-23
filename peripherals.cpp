
#include "peripherals.h"

// See data sheet for pin placements, adjust as necessary. 

//---------------------------------------------------------------------------
//----------------------------------Servos-----------------------------------
//---------------------------------------------------------------------------

bool servo_mode = true;

// Angle of the servos from -90 to 90.
// Both servos on timer 1

void init_servo_0() {
    DDRB |= (1 << PB1); // Set PB1 (OC1A) as output for PWM
    TCCR1A |= (1 << WGM11) | (1 << COM1A1); // Fast PWM, non-inverting mode, timer 1
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler = 8
    ICR1 = 39999; // Set TOP for 50Hz PWM frequency, maximum : 4800 
    OCR1A = 3000; // Set the pulse width for Servo 0 (middle position) - 0 to 39999
}

void init_servo_1() {
    DDRB |= (1 << PB2); // Set PB2 (OC1B) as output for PWM
    TCCR1A |= (1 << WGM11) | (1 << COM1B1); // Fast PWM, non-inverting mode, timer 1
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler = 8
    ICR1 = 39999; // Set TOP for 50Hz PWM frequency
    OCR1B = 3000; // Set the pulse width for Servo 1 (middle position) - 0 to 39999
}

void set_servo_0(int8_t angle) {
    //convert from -90,90 to 0,180
    angle +=90;
    // Clamp angle from 0 to 180
    if (angle > 180) angle = 180;
    if (angle < 0) angle = 0;
  
    //Pulse width calculation - from 600 to 2400
    uint16_t pulseWidth = ((uint32_t)angle * (2400 - 600) / 180) + 600;

    // Convert pulse width to timer counts (each count is 0.5µs with prescaler of 8)
    OCR1A = pulseWidth * 2; // Set the pulse width for Servo 1 (middle position) - 0 to 39999
}

void set_servo_1(int8_t angle) {
    //convert from -90,90 to 0,180
    angle +=90;
    // Clamp angle from 0 to 180
    if (angle > 180) angle = 180;
    if (angle < 0) angle = 0;
  
    //Pulse width calculation - from 600 to 2400
    uint16_t pulseWidth = ((uint32_t)angle * (2400 - 600) / 180) + 600;
  
    // Convert pulse width to timer counts (each count is 0.5µs with prescaler of 8)
    OCR1B = pulseWidth * 2; // Set the timer compare value - from 1200 to 4800
}

//---------------------------------------------------------------------------
//----------------------------------Fans-------------------------------------
//---------------------------------------------------------------------------

// All fan speeds are based on a percentage.
// Thrust fans (1 and 2) use timer 0

void init_fan_0(){
    DDRD |= (1 << PD6); // Set PD6 (OC0A) 

    // Fast PWM, non-inverting, Prescaler = 8 → ~7.8kHz PWM frequency
    TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);
    TCCR0B |= (1 << CS01);

    OCR0A = 0; // Fan 2 (0-255)
}

void init_fan_1(){
    DDRD |= (1 << PD5); // Set PD5 (OC0B) as output

    // Fast PWM, non-inverting, Prescaler = 8 → ~7.8kHz PWM frequency
    TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0B1);
    TCCR0B |= (1 << CS01);

    OCR0B = 0; // Fan 1 (0-255)
}

void init_fan_2(){
    // lift fan => software pwm
}

void set_fan_0(uint8_t percentages){
    //convert percentage to fan duty cycle.
    OCR0A = (percentages * 255) /100;
}

void set_fan_1(uint8_t percentages){
    //convert percentage to fan duty cycle.
    OCR0B = (percentages * 255) /100; 
}

void set_fan_2(uint8_t percentages){
    // lift fan => software pwm
}







