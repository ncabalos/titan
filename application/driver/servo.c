#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <p24Fxxxx.h>
#include "../hardware_config.h"

#define SERVO_CHANNEL_COUNT 8
#define SERVO_MAX_VALUE 1000

enum {
    SERVO_STATE_START,
    SERVO_STATE_PULSE,
    SERVO_STATE_END,
    SERVO_STATE_COUNT
};

struct servo_info_block {
    bool enabled;
    uint16_t value;
};

struct servo_info_block servos[SERVO_CHANNEL_COUNT];

static uint16_t servo_state;
static uint16_t servo_channel;
static uint16_t servo_value;

static uint16_t servo_pr_start;
static uint16_t servo_pr_pulse;
static uint16_t servo_pr_end;

bool servo_set_value(uint16_t channel, uint16_t value)
{
    struct servo_info_block * sib;

    if(channel >= SERVO_CHANNEL_COUNT) {
        return false;
    }

    if(value > SERVO_MAX_VALUE) {
        return false;
    }

    sib = servos + channel;
    sib->value = value;
    return true;
}

bool servo_set_enabled(uint16_t channel, bool enabled)
{
    struct servo_info_block * sib;

    if(channel >= SERVO_CHANNEL_COUNT) {
        return false;
    }

    sib = servos + channel;
    sib->value = enabled;
    return true;
}

void servo_init(void)
{
    servo_state = SERVO_STATE_START;
    servo_value = 500;
    servo_channel = 0;
    /* 
     * this is where we initialize the timer that will be used by the servo
     * module. Lets use timer (TBD)
     */
}

void update_pin(bool state)
{
    switch(servo_channel) {
        case 0:
            SERVO_0 = state;
            break;

        case 1:
            SERVO_1 = state;
            break;

        case 2:
            SERVO_2 = state;
            break;

        case 3:
            SERVO_3 = state;
            break;

        case 4:
            SERVO_4 = state;
            break;

        case 5:
            SERVO_5 = state;
            break;

        case 6:
            SERVO_6 = state;
            break;

        case 7:
            SERVO_7 = state;
            break;
    }
}

void servo_update(void)
{
    struct servo_info_block * sib;

    switch(servo_state) {
        case SERVO_STATE_START:
            if(servo_pr_pulse > 0) {
                PR2 = servo_pr_pulse;
                servo_state = SERVO_STATE_PULSE;
                update_pin(true);
            } else {
                PR2 = servo_pr_end;
                servo_state = SERVO_STATE_END;
                update_pin(false);
            }

            break;

        case SERVO_STATE_PULSE:
            PR2 = servo_pr_end;
            servo_state = SERVO_STATE_END;
            update_pin(false);
            break;

        case SERVO_STATE_END:
            /* update pr values */
            servo_channel++;

            if(servo_channel == SERVO_CHANNEL_COUNT) {
                servo_channel = 0;
            }

            sib = servos + servo_channel;
            servo_pr_start = 500;
            servo_pr_pulse = 2000 + sib->value * 2;
            servo_pr_end = 4500 - servo_pr_pulse;
            PR2 = servo_pr_start;
            servo_state = SERVO_STATE_START;
            update_pin(false);
            break;
    }
}

