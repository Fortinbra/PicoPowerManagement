#include "include/pin_setup.h"

void setup_pins() {
    // Set up PWM for fan control
    gpio_set_function(FAN_ONE_PWM_PIN, GPIO_FUNC_PWM);
    gpio_set_function(FAN_TWO_PWM_PIN, GPIO_FUNC_PWM);
    uint slice_num_fan_one = pwm_gpio_to_slice_num(FAN_ONE_PWM_PIN);
    uint slice_num_fan_two = pwm_gpio_to_slice_num(FAN_TWO_PWM_PIN);
    pwm_set_enabled(slice_num_fan_one, true);
    pwm_set_enabled(slice_num_fan_two, true);

    // Set up RPM input pins
    gpio_set_function(FAN_ONE_RPM_PIN, GPIO_FUNC_SIO);
    gpio_set_function(FAN_TWO_RPM_PIN, GPIO_FUNC_SIO);
    gpio_set_dir(FAN_ONE_RPM_PIN, GPIO_IN);
    gpio_set_dir(FAN_TWO_RPM_PIN, GPIO_IN);

    // Set up other GPIO pins
    gpio_init(POWER_BUTTON_PIN);
    gpio_set_dir(POWER_BUTTON_PIN, GPIO_IN);
    gpio_pull_up(POWER_BUTTON_PIN); // Enable pull-up resistor

    gpio_init(DISPLAY_PI_PIN);
    gpio_set_dir(DISPLAY_PI_PIN, GPIO_OUT);
    gpio_pull_up(DISPLAY_PI_PIN); // Enable pull-up resistor

    gpio_init(PI_ONE_PIN);
    gpio_set_dir(PI_ONE_PIN, GPIO_OUT);
    gpio_pull_up(PI_ONE_PIN); // Enable pull-up resistor

    gpio_init(PI_TWO_PIN);
    gpio_set_dir(PI_TWO_PIN, GPIO_OUT);
    gpio_pull_up(PI_TWO_PIN); // Enable pull-up resistor

    gpio_init(PI_THREE_PIN);
    gpio_set_dir(PI_THREE_PIN, GPIO_OUT);
    gpio_pull_up(PI_THREE_PIN); // Enable pull-up resistor

    gpio_init(PI_FOUR_PIN);
    gpio_set_dir(PI_FOUR_PIN, GPIO_OUT);
    gpio_pull_up(PI_FOUR_PIN); // Enable pull-up resistor

    gpio_init(PSU_PIN);
    gpio_set_dir(PSU_PIN, GPIO_OUT);
    gpio_put(PSU_PIN, 0); // Set the default state of the PSU pin to low
}