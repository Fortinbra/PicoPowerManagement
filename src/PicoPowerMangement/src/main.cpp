#include <stdio.h>
#include "pico/stdlib.h"
#include "include/pin_setup.h"
#include "include/uart_handler.h"

#define LONG_PRESS_DURATION_MS 5000 // Duration to consider a long press (5 seconds)

int main()
{
    stdio_init_all();
    setup_pins();
    init_uart();

    bool psu_on = false;
    absolute_time_t press_start_time;

    // Track the state of the Pi pins
    bool pi_one_on = false;
    bool pi_two_on = false;
    bool pi_three_on = false;
    bool pi_four_on = false;

    while (true)
    {
        // Check if the power button is pressed (active low)
        if (gpio_get(POWER_BUTTON_PIN) == 0)
        {
            if (!psu_on)
            {
                // If PSU is off, turn it on
                gpio_put(PSU_PIN, 1);
                psu_on = true;
                press_start_time = get_absolute_time();

                // Mimic the press on Pi pins (active low)
                gpio_put(PI_ONE_PIN, 0);
                gpio_put(PI_TWO_PIN, 0);
                gpio_put(PI_THREE_PIN, 0);
                gpio_put(PI_FOUR_PIN, 0);
                gpio_put(DISPLAY_PI_PIN, 0); // Set DISPLAY_PI_PIN low
                pi_one_on = pi_two_on = pi_three_on = pi_four_on = true;
            }
            else
            {
                // If PSU is on, check for long press
                if (absolute_time_diff_us(press_start_time, get_absolute_time()) / 1000 >= LONG_PRESS_DURATION_MS)
                {
                    // Long press detected, force PSU off
                    gpio_put(PSU_PIN, 0);
                    psu_on = false;

                    // Mimic the long press on Pi pins (active low)
                    gpio_put(PI_ONE_PIN, 1);
                    gpio_put(PI_TWO_PIN, 1);
                    gpio_put(PI_THREE_PIN, 1);
                    gpio_put(PI_FOUR_PIN, 1);
                    gpio_put(DISPLAY_PI_PIN, 1); // Set DISPLAY_PI_PIN high
                    pi_one_on = pi_two_on = pi_three_on = pi_four_on = false;
                }
            }
        }
        else
        {
            // Button is not pressed, reset press start time
            press_start_time = get_absolute_time();
        }

        // Handle UART commands
        handle_uart_commands();

        sleep_ms(1000);
    }
}
