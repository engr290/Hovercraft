
// IMPORTANT!!!!!!!
// set interrupt on pin 2 
void init_gpio_pins{
  DDRD &= ~(1 << PD2);  // Set PD2 as input
  PORTD |= (1 << PD2);  // Enable internal pull-up resistor on PD2

  EICRA |= (1 << ISC00);  // Trigger on any logical change
  EIMSK |= (1 << INT0);   // Enable external interrupt on INT0
}