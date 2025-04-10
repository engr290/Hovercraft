
#include "peripherals.h"
#include "c_math.h"

float imu_data[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // initialize to 0

void init_timer_0(){

  DDRD |= (1 << PD5) | (1 << PD6);

  // Clear Timer0 Control Registers
  TCCR0A = 0;
  TCCR0B = 0;

  // Set Fast PWM Mode: WGM01 = 1, WGM00 = 1
  TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0A1) | (1 << COM0B1);
  // Set prescaler to 64 (adjust as needed)
  TCCR0B |= (1 << CS01);
}

void init_timer_1(){
  DDRB |= (1 << PB1) | (1 << PB2); // Set PB1 (OC1A) as output for PWM
  TCCR1A = (1 << WGM11) | (1 << COM1A1) | (1 << COM1B1); // Fast PWM, non-inverting mode
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler = 8
  ICR1 = 39999; // Set TOP for 50Hz PWM frequency
  OCR1A = 3000; // Initialize to center position (1.5ms pulse width)
  OCR1B = 3000;
}

void init_timer_2(){
  TCCR2A= (1<<WGM21);//set to CTC mode
  TCCR2B=(1<<CS22);//to set the prescaler to 64
  OCR2A = 249; //counter reset back 249->0,1,2,3,4,....
  TIMSK2 = (1<<OCIE2A); //1ms
  TIMSK2 = (1 << OCIE2A); // Enable Timer2 Compare A interrupt
}

void set_servo_A(int16_t angle) {

  angle += 90;

  if (angle > 180)
    angle = 180;
  else if(angle < 0)
    angle = 0;

  uint16_t pulseWidth = angle * 10.694 + 575;
  // Convert pulse width to timer counts (each count is 0.5us with prescaler of 8)
  OCR1A = pulseWidth * 2; // Set the timer compare value
}

void set_servo_B(int16_t angle) {
  
  angle += 90;

  
  if (angle > 180)
    angle = 180;
  else if(angle < 0)
    angle = 0;

  uint16_t pulseWidth = angle * 10.694 + 575;
  // Convert pulse width to timer counts (each count is 0.5us with prescaler of 8)
  OCR1B = pulseWidth * 2; // Set the timer compare value
}

void set_fan_A(uint8_t power) {
  if (power > 255) {
    power = 255;
  }
  else if(power < 0) {
    power = 0;
  }
  OCR0B = power; 
}

void set_fan_B(uint8_t power) {
  if (power > 255) {
    power = 255;
  }
  else if(power < 0) {
    power = 0;
  }
  OCR0A = power;
}


void init_lift(){
  DDRD |= (1  << PD7);
}

void set_lift(bool on){
  if (on)
    PORTD |= (1 << PD7);
  else
    PORTD &= ~(1 << PD7);
}

void init_imu(){
  c_i2c_start();
  c_i2c_write(IMU_ADDR << 1 | 0); // Write address of IMU ( `7 bit address` + `0` )
  c_i2c_write(IMU_PWR_REG);
  c_i2c_write(IMU_250); // Starting imu with default mode | refere to docs for other modes
  c_i2c_stop();
}

void get_one_round_IMU_data() {

  
  uint8_t data[14]; // I2C response buffer

  c_i2c_start();
  c_i2c_write(IMU_ADDR << 1 | 0); // Write address of IMU ( `7 bit address` + `0` )
  c_i2c_write(IMU_X_ACCEL_REG);
  c_i2c_stop();

  c_i2c_start();
  c_i2c_write(IMU_ADDR << 1 | 1); // Read address of IMU ( `7 bit address` + `1` )
  // read 14 consecutive registers
  for(uint8_t i=0; i < 13; i++)
    data[i] = c_i2c_read_ack();
  data[13] = c_i2c_read_nack();


  // TODO
  // Modify it based on the setting
  imu_data[6] = ( ((int16_t)data[0] << 8) | data[1] ) / ACCEL_SCALE; // x
  imu_data[7] = ( ((int16_t)data[2] << 8) | data[3] ) / ACCEL_SCALE; // y
  imu_data[8] = ( ((int16_t)data[4] << 8) | data[5] ) / ACCEL_SCALE; // z
  imu_data[9] = ( ((int16_t)data[8] << 8) | data[9] ) / GYRO_SCALE;    // roll
  imu_data[10] = ( ((int16_t)data[10] << 8) | data[11] ) / GYRO_SCALE;  // pitch
  imu_data[11] = ( ((int16_t)data[12] << 8) | data[13] ) / GYRO_SCALE;  // yaw

}


// TODO
// Check the stop ones
void get_imu_data(){

  uint16_t times = 200;

  // Initial measurement as first average sample.
  get_one_round_IMU_data();
  imu_data[0] = imu_data[6]; // x acceleration
  imu_data[1] = imu_data[7]; // y acceleration
  imu_data[2] = imu_data[8]; // z acceleration
  imu_data[3] = imu_data[9]; // roll
  imu_data[4] = imu_data[10]; // pitch
  imu_data[5] = imu_data[11]; // yaw

  // Print initial averaged values.

  // Averaging loop using a corrected incremental formula.
  // Here we treat the initial sample as sample 1, and for each iteration we update the average correctly.
  for (int i = 1; i < times; i++) {
    get_one_round_IMU_data();

    // Print the new sample readings.

    // Total count of samples so far.
    float count = i + 1;

    // Update the running average using the incremental formula:
    // new_average = old_average + (new_sample - old_average) / count
    float old_x = imu_data[0];
    imu_data[0] = old_x + (imu_data[6] - old_x) / count;
    float old_y = imu_data[1];
    imu_data[1] = old_y + (imu_data[7] - old_y) / count;
    float old_z = imu_data[2];
    imu_data[2] = old_z + (imu_data[8] - old_z) / count;
    float old_roll = imu_data[3];
    imu_data[3] = old_roll + (imu_data[9] - old_roll) / count;
    float old_pitch = imu_data[4];
    imu_data[4] = old_pitch + (imu_data[10] - old_pitch) / count;
    float old_yaw = imu_data[5];
    imu_data[5] = old_yaw + (imu_data[11] - old_yaw) / count;

    // Print the updated average after this iterat
  }  




}


void c_delay(uint32_t ms) {
	unsigned long target_count = system_time + ms;  // Calculate when to stop (target count)
	
	// Wait until the timer_count reaches the target_count
	while (system_time < target_count);
}

void init_forward_ir() {
  ADMUX = (ADMUX & 0x3F);  // reset REFS1 and REFS0 to 0
  ADMUX |= (1 << REFS0);  // REFS1 = 0, REFS0 = 1
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  ADMUX = (ADMUX & 0xF0) | (0 & 0x07);
}

uint16_t read_forward_ir(){
  ADCSRA |= (1 << ADSC);   // start reading

	// i is there for timeout
	for(int i = 0; i < 10000 && (ADCSRA & (1 << ADSC)); i++);
	
	return ADC;
}