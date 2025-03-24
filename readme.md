# Hovercraft Control System
This is a control system designed for a simple hovercraft, powered by an Arduino Nano. The hovercraft is tasked with navigating through a blow maze within a two-minute time frame.
**TODO: Add the maze.**

To ensure accurate tracking of the yaw angle, an IMU Kalman filter is implemented for data correction. The mission will be considered complete once a stop sign is detected by a digital IR sensor, which triggers an interrupt to turn off the system.
# Pin Setup:
The hovercraft is equipped with three fans, two servo motors, two analog IR sensors, one digital IR sensor, and an IMU.

**Pin Configuration table**

| Perperal | Pin |
| :---: | :---:|
| Servo0 | OC2A ( Pin 11 ) |
| Servo1 | OC2B ( Pin 3 ) |
| Fan0 (lift) | OC1A ( Pin 9 ) |
| Fan 1 | OC0A ( Pin 6 ) |
| Fan 2 | OC0B ( Pin 5 ) |
| Front IR | TBD |
| Side IR | TBD |
| digital IR | TBD |
| IMU | I2C bus lines |

