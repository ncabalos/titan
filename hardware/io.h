/*
 * File:   io.h
 * Author: ncabalos
 *
 * Created on March 11, 2014, 10:34 PM
 */

#ifndef IO_H
#define	IO_H

typedef enum {
    IO_TYPE_NULL,
    IO_TYPE_UART,
    IO_TYPE_I2C,
    IO_TYPE_SPI,
    IO_TYPE_COUNT
} io_device_type;

typedef void (* write_func)(const uint8_t * data, uint16_t size);
typedef void (* read_func)(uint8_t * data, uint16_t size);

typedef struct IO_DEVICE_S {
    uint16_t id;
    uint16_t type;
    write_func write;
    read_func read;
} IO_DEVICE;


void io_write(IO_DEVICE * device, const uint8_t * data, uint16_t size);
void io_read(IO_DEVICE * device, uint8_t * data, uint16_t size);

#endif	/* IO_H */

