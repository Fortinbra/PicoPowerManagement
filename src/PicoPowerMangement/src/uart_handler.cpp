#include "include/pin_setup.h"
#include "include/uart_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UART_ID uart1
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

void init_uart()
{
    // Initialize UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
}

void handle_uart_commands()
{
    // Check if there is data available to read
    if (uart_is_readable(UART_ID))
    {
        char command = uart_getc(UART_ID);
        // Handle the command
        switch (command)
        {
        case 'S': // Shutdown command
        {
            // Read the parameter (number)
            char param_str[10];
            int i = 0;
            while (uart_is_readable(UART_ID) && i < sizeof(param_str) - 1)
            {
                char c = uart_getc(UART_ID);
                if (c == '\n' || c == '\r')
                    break;
                param_str[i++] = c;
            }
            param_str[i] = '\0';

            if (i == 0)
            {
                // No argument passed, shutdown all
                uart_puts(UART_ID, "Shutdown all\n");

                // Mimic the press on all Pi pins (active low)
                gpio_put(PI_ONE_PIN, 0);
                gpio_put(PI_TWO_PIN, 0);
                gpio_put(PI_THREE_PIN, 0);
                gpio_put(PI_FOUR_PIN, 0);
                gpio_put(DISPLAY_PI_PIN, 0);

                sleep_ms(500); // Short press duration

                // Release the press on all Pi pins (active low)
                gpio_put(PI_ONE_PIN, 1);
                gpio_put(PI_TWO_PIN, 1);
                gpio_put(PI_THREE_PIN, 1);
                gpio_put(PI_FOUR_PIN, 1);
                gpio_put(DISPLAY_PI_PIN, 1);
            }
            else
            {
                // Argument passed, shutdown specific Pi pin
                int shutdown_number = atoi(param_str);
                char response[50];
                snprintf(response, sizeof(response), "Shutdown command received with parameter: %d\n", shutdown_number);
                uart_puts(UART_ID, response);

                switch (shutdown_number)
                {
                case 1:
                    gpio_put(PI_ONE_PIN, 0);
                    sleep_ms(500); // Short press duration
                    gpio_put(PI_ONE_PIN, 1);
                    break;
                case 2:
                    gpio_put(PI_TWO_PIN, 0);
                    sleep_ms(500); // Short press duration
                    gpio_put(PI_TWO_PIN, 1);
                    break;
                case 3:
                    gpio_put(PI_THREE_PIN, 0);
                    sleep_ms(500); // Short press duration
                    gpio_put(PI_THREE_PIN, 1);
                    break;
                case 4:
                    gpio_put(PI_FOUR_PIN, 0);
                    sleep_ms(500); // Short press duration
                    gpio_put(PI_FOUR_PIN, 1);
                    break;
                case 5:
                    gpio_put(DISPLAY_PI_PIN, 0);
                    sleep_ms(500); // Short press duration
                    gpio_put(DISPLAY_PI_PIN, 1);
                    break;
                default:
                    uart_puts(UART_ID, "Invalid shutdown parameter\n");
                    break;
                }
            }
            break;
        }
        case 'F': // Fans command
        {
            // Read the parameters (numbers)
            char param_str[20];
            int i = 0;
            while (uart_is_readable(UART_ID) && i < sizeof(param_str) - 1)
            {
                char c = uart_getc(UART_ID);
                if (c == '\n' || c == '\r')
                    break;
                param_str[i++] = c;
            }
            param_str[i] = '\0';

            int param_count = 0;
            int params[2] = {0, 0};
            char *token = strtok(param_str, " ");
            while (token != NULL && param_count < 2)
            {
                params[param_count++] = atoi(token);
                token = strtok(NULL, " ");
            }

            if (param_count == 0)
            {
                // No arguments passed, return current fan speeds
                char response[100];
                snprintf(response, sizeof(response), "Fan 1 RPM: %d, Fan 2 RPM: %d\n", gpio_get(FAN_ONE_RPM_PIN), gpio_get(FAN_TWO_RPM_PIN));
                uart_puts(UART_ID, response);
            }
            else if (param_count == 1)
            {
                // One argument passed, set both fans to the same speed
                int speed = params[0];
                pwm_set_gpio_level(FAN_ONE_PWM_PIN, speed);
                pwm_set_gpio_level(FAN_TWO_PWM_PIN, speed);
                char response[50];
                snprintf(response, sizeof(response), "Set both fans to speed: %d\n", speed);
                uart_puts(UART_ID, response);
            }
            else if (param_count == 2)
            {
                // Two arguments passed, set each fan to the respective speed
                int speed1 = params[0];
                int speed2 = params[1];
                pwm_set_gpio_level(FAN_ONE_PWM_PIN, speed1);
                pwm_set_gpio_level(FAN_TWO_PWM_PIN, speed2);
                char response[50];
                snprintf(response, sizeof(response), "Set fan 1 to speed: %d, fan 2 to speed: %d\n", speed1, speed2);
                uart_puts(UART_ID, response);
            }
            break;
        }
        case 'E': // Emergency Stop command
        {
            uart_puts(UART_ID, "Emergency Stop\n");

            // Turn off the PSU immediately
            gpio_put(PSU_PIN, 0);

            // Halt the firmware
            while (true)
            {
                // Infinite loop to halt the firmware
            }
            break;
        }
        default:
            uart_puts(UART_ID, "Unknown command\n");
            break;
        }
    }
}