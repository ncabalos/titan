/*
 * File:   uart.h
 * Author: ncabalos
 *
 * Created on May 18, 2014, 1:18 PM
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

#define UART_BUFFER_SIZE 32
#define UART_COUNT 4

typedef struct UART_MODULE_S {
    bool in_use;
    uint16_t baud_rate;
    uint8_t tx_buffer_data[UART_BUFFER_SIZE];
    uint8_t rx_buffer_data[UART_BUFFER_SIZE];
    struct queue tx_buffer;
    struct queue rx_buffer;
} UART_MODULE;

UART_MODULE * uart_init(uint16_t module_number, uint16_t baud_rate);
bool uart_write(UART_MODULE * uart, uint8_t * data, uint16_t len);
bool uart_read(UART_MODULE * uart, uint8_t * data, uint16_t len);
void uart_reset_tx_buffer(UART_MODULE * uart);
void uart_reset_rx_buffer(UART_MODULE * uart);
void uart_reset_all_buffer(UART_MODULE * uart);

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

