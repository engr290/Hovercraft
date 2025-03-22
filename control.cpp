#include "globals.h"
#include "Control.h"

void init_hovercraft() {
    init_servo_0();
    init_servo_1();

    set_servo_0(0);
    set_servo_1(0);

    init_fan_0();
    init_fan_1();
    init_fan_2();

    // TODO
    // Might not need 100 percent duty cycle
    set_fan_0(100);

}

void move_forward() {

}

void angle_adjust(int16_t angle) {

}

void turn_off() {

}

void stop() {

}
