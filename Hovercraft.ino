
#include "peripherals.h"
#include "globals.h"
#include "c_math.h"

float system_data[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

// 350 side

int main(){

  cli();
  sei();

  init_timer_0();
  init_timer_1();
  init_timer_2();
  c_i2c_init();
  init_imu();
  init_lift();
  init_side_ir();

  set_servo_A(0);
  set_servo_B(0);
  
  set_lift(true);

  set_fan_A(0); // set both fans full power
  set_fan_B(0);

  c_delay(1000);
  Serial.begin(9600);
  Serial.println("starting");

  unsigned long prev_time = system_time;


  c_delay(1000);

  get_imu_data();

  set_fan_A(250);
  set_fan_B(220);

  int stationary_count = 0;
  
  int8_t yaw_fix = 1;
  uint16_t turns_done = 0;

  
  
  while(1) {

    get_imu_data();


    float dt = float(system_time - prev_time) / 1000.0; // converting to sec
    system_data[3] = integral(imu_data[0] * Gravity, system_data[3], dt) / 100; // x_v
    system_data[8] = integral(imu_data[5], system_data[8], dt); // yaw

    if(fabs(imu_data[0]) < 0.06) {
          stationary_count++;
    }
    else{
      stationary_count = 0;
    }

    // Serial.println(stationary_count);

    prev_time = system_time;


    if(stationary_count > 25) {
      //system_data[8] = 0;
      system_data[8] += yaw_fix * 90;
      turns_done++;
      stationary_count = 0;

      // TODO
      // Check with zeroing the angle ?????


      // uint16_t side_val = read_side_ir();

      // if (side_val < 350) {
      //   yaw_fix = -1;
      // }
      // else{
      //   yaw_fix = 1;
      // }
    }

    if(turns_done > 1){
      turns_done = 0;
      yaw_fix *= -1;
    }
    
    set_servo_A(-90 + 2 * system_data[8]);
    set_servo_B(90 + 2 * system_data[8]);


  }
  
  
  // Turn off everything
  /*set_lift(false);
  set_fan_A(0);
  set_fan_B(0);
  set_servo_A(0);
  set_servo_B(0);*/
  
}