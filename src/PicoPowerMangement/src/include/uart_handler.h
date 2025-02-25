#ifndef UART_HANDLER_H
#define UART_HANDLER_H

#include "pico/stdlib.h"
#include "hardware/uart.h"

void init_uart();
void handle_uart_commands();

#endif // UART_HANDLER_H