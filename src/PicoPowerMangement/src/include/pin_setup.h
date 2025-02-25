#ifndef PIN_SETUP_H
#define PIN_SETUP_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Define pins for other functionalities
#define FAN_ONE_PWM_PIN 4
#define FAN_TWO_PWM_PIN 6
#define FAN_ONE_RPM_PIN 9
#define FAN_TWO_RPM_PIN 11
#define POWER_BUTTON_PIN 15
#define DISPLAY_PI_PIN 21
#define PI_ONE_PIN 22
#define PI_TWO_PIN 24
#define PI_THREE_PIN 25
#define PI_FOUR_PIN 26
#define PSU_PIN 27

void setup_pins();

#endif // PIN_SETUP_H