#include <p24Fxxxx.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "io.h"
#include "../queue.h"
#include "uart.h"

static UART_MODULE modules[UART_COUNT];

static bool get_uart_module(UART_MODULE * module, uint16_t id)
{
    if(id >= UART_COUNT) {
        return false;
    }

    module = modules + id;
    return true;
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
    /* TODO: initialize UART hardware */
    /* uart_init(module_number, baud_rate); */
    return module;
}
bool uart_write(uint16_t module_number, uint8_t * data, uint16_t len)
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
        result = queue_enqueue(&module->tx_buffer, data++);

        if(result == false) {
            return false;
        }
    }

    uart_start_tx(module_number);
    return true;
}
bool uart_read(uint16_t module_number, uint8_t * data, uint16_t len)
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

void uart_init(uint16_t module_number, uint16_t baud_rate)
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

void uart_start_tx(uint16_t module_number)
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

