
#include "peripherals.h"
#include "globals.h"


int main(){

  init_timer_0();
  init_timer_1();


  init_lift();
  set_lift(true);
  set_servo_A(90);
  set_servo_B(-90);


  set_fan_A(255);
  set_fan_B(255);


  while(1) {
    
  }

}