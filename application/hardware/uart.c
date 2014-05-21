#include <p24Fxxxx.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "../queue.h"
#include "uart.h"

static UART_MODULE modules[UART_COUNT];

static void hardware_init(uint16_t module_number, uint16_t baud_rate);
static void hardware_start_tx(uint16_t module_number);

static bool get_uart_module(UART_MODULE * module, uint16_t id)
{
    if(id >= UART_COUNT) {
        return false;
    }

    module = modules + id;
    return true;
}

static bool get_module_number(UART_MODULE * module, uint16_t * index)
{
    uint16_t i;

    if(module == NULL) {
        return false;
    }

    for(i = 0; i < UART_COUNT; i++) {
        if(&modules[i] == module) {
            *index = i;
            return true;
        }
    }

    return false;
}

UART_MODULE * uart_init(uint16_t module_number, uint16_t baud_rate)
{
    UART_MODULE * module = NULL;
    bool result;
    result = get_uart_module(module, module_number);

    if(result == false) {
        return NULL;
    }

    module->in_use = true;
    module->baud_rate = baud_rate;
    queue_register(&module->tx_buffer, module->tx_buffer_data, UART_BUFFER_SIZE,
                   sizeof(uint8_t));
    queue_register(&module->rx_buffer, module->rx_buffer_data, UART_BUFFER_SIZE,
                   sizeof(uint8_t));
    hardware_init(module_number, baud_rate);
    return module;
}
bool uart_write(UART_MODULE * module, uint8_t * data, uint16_t len)
{
    bool result;
    uint16_t module_number;

    if(module == NULL) {
        return false;
    }

    if(module->in_use == false) {
        return false;
    }

    while(len--) {
        result = queue_enqueue(&module->tx_buffer, data++);

        if(result == false) {
            return false;
        }
    }

    if(get_module_number(module, &module_number) == false) {
        return false;
    }

    hardware_start_tx(module_number);
    return true;
}
bool uart_read(UART_MODULE * module, uint8_t * data, uint16_t len)
{
    bool result;

    if(module == NULL) {
        return false;
    }

    if(module->in_use == false) {
        return false;
    }

    while(len--) {
        result = queue_dequeue(&module->rx_buffer, data++);

        if(result == false) {
            return false;
        }
    }

    return true;
}

bool uart_tx_callback(uint16_t module_number, uint8_t * data, uint16_t len)
{
    UART_MODULE * module = NULL;
    bool result;
    result = get_uart_module(module, module_number);

    if(result == false) {
        return false;
    }

    if(module->in_use == false) {
        return false;
    }

    while(len--) {
        result = queue_dequeue(&module->tx_buffer, data++);

        if(result == false) {
            return false;
        }
    }

    return true;
}

bool uart_rx_callback(uint16_t module_number, uint8_t * data, uint16_t len)
{
    UART_MODULE * module = NULL;
    bool result;
    result = get_uart_module(module, module_number);

    if(result == false) {
        return false;
    }

    if(module->in_use == false) {
        return false;
    }

    while(len--) {
        result = queue_enqueue(&module->rx_buffer, data++);

        if(result == false) {
            return false;
        }
    }

    return true;
}

void uart_reset_tx_buffer(UART_MODULE * uart)
{
    if(uart == NULL) {
        return;
    }

    uart->tx_buffer.count = 0;
    uart->tx_buffer.in = 0;
    uart->tx_buffer.out = 0;
    memset(uart->tx_buffer_data, 0, UART_BUFFER_SIZE);
}

void uart_reset_rx_buffer(UART_MODULE * uart)
{
    if(uart == NULL) {
        return;
    }

    uart->rx_buffer.count = 0;
    uart->rx_buffer.in = 0;
    uart->rx_buffer.out = 0;
    memset(uart->rx_buffer_data, 0, UART_BUFFER_SIZE);
}

void uart_reset_all_buffer(UART_MODULE * uart)
{
    if(uart == NULL) {
        return;
    }

    uart_reset_tx_buffer(uart);
    uart_reset_rx_buffer(uart);
}

void hardware_init(uint16_t module_number, uint16_t baud_rate)
{
    switch(module_number) {
        case 0:
            break;

        case 1:
            break;

        case 2:
            break;

        case 3:
            break;

        default:
            break;
    }
}

void hardware_start_tx(uint16_t module_number)
{
    switch(module_number) {
        case 0:
            IFS0bits.U1TXIF = 1;
            break;

        case 1:
            IFS1bits.U2TXIF = 1;
            break;

        case 2:
            IFS5bits.U3TXIF = 1;
            break;

        case 3:
            IFS5bits.U4TXIF = 1;
            break;

        default:
            break;
    }
}

