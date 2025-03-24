#include "c_drivers.h"

unsigned long timer_count = 0;

// IMPORTANT!!!!!!!
// set interrupt on pin 2 
void init_gpio_pins(){
  DDRD &= ~(1 << PD2);  // Set PD2 as input
  PORTD |= (1 << PD2);  // Enable internal pull-up resistor on PD2

  EICRA |= (1 << ISC00);  // Trigger on any logical change
  EIMSK |= (1 << INT0);   // Enable external interrupt on INT0
}



void c_init_timer2()//PLACE C TIMER2
{
  // put your setup code here, to run once:
  TCCR2A= (1<<WGM21);//set to CTC mode
  TCCR2B=(1<<CS22);//to set the prescaler to 64
  OCR2A = 249; //counter reset back 249->0,1,2,3,4,....
  TIMSK2 = (1<<OCIE2A); //1ms
  TIMSK2 = (1 << OCIE2A); // Enable Timer2 Compare A interrupt
}

uint64_t c_current_time()
{
  return timer_count;
}

void c_delay_milli(unsigned long ms)
{
 uint64_t target = c_current_time() + ms;

 while(c_current_time() < target);
}
