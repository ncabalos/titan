/*
 * File:   hardware_config.h
 * Author: ncabalos
 *
 * Created on May 20, 2014, 10:28 PM
 */

#ifndef HARDWARE_CONFIG_H
#define	HARDWARE_CONFIG_H

#include <p24Fxxxx.h>

/* Initialize io pins */

#define LED_0 LATGbits.LATG0
#define init_LED_0()        \
{                           \
    TRISGbits.TRISG0 = 0;   \
    LATGbits.LATG0 = 0;     \
}

#define LED_1 LATGbits.LATG1
#define init_LED_1()        \
{                           \
    TRISGbits.TRISG1 = 0;   \
    LATGbits.LATG1 = 0;     \
}

#define LED_2 LATFbits.LATF1
#define init_LED_2()        \
{                           \
    TRISFbits.TRISF1 = 0;   \
    LATFbits.LATF1 = 0;     \
}

#define LED_3 LATFbits.LATF0
#define init_LED_3()        \
{                           \
    TRISFbits.TRISF0 = 0;   \
    LATFbits.LATF0 = 0;     \
}

#define LED_4 LATDbits.LATD7
#define init_LED_4()        \
{                           \
    TRISDbits.TRISD7 = 0;   \
    LATDbits.LATD7 = 0;     \
}

#define LED_5 LATDbits.LATD6
#define init_LED_5()        \
{                           \
    TRISDbits.TRISD6 = 0;   \
    LATDbits.LATD6 = 0;     \
}

#define LED_6 LATDbits.LATD5
#define init_LED_6()        \
{                           \
    TRISDbits.TRISD5 = 0;   \
    LATDbits.LATD5 = 0;     \
}

#define LED_7 LATDbits.LATD11
#define init_LED_7()        \
{                           \
    TRISDbits.TRISD11 = 0;  \
    LATDbits.LATD11 = 0;    \
}

#define init_LEDs()         \
{                           \
    init_LED_0()            \
    init_LED_1()            \
    init_LED_2()            \
    init_LED_3()            \
    init_LED_4()            \
    init_LED_5()            \
    init_LED_6()            \
    init_LED_7()            \
}

#define SERVO_0 LATEbits.LATE0
#define init_SERVO_0()      \
{                           \
    TRISEbits.TRISE0 = 0;   \
    LATEbits.LATE0 = 0;     \
}

#define SERVO_1 LATEbits.LATE1
#define init_SERVO_1()      \
{                           \
    TRISEbits.TRISE1 = 0;   \
    LATEbits.LATE1 = 0;     \
}

#define SERVO_2 LATEbits.LATE2
#define init_SERVO_2()      \
{                           \
    TRISEbits.TRISE2 = 0;   \
    LATEbits.LATE2 = 0;     \
}

#define SERVO_3 LATEbits.LATE3
#define init_SERVO_3()      \
{                           \
    TRISEbits.TRISE3 = 0;   \
    LATEbits.LATE3 = 0;     \
}

#define SERVO_4 LATEbits.LATE4
#define init_SERVO_4()      \
{                           \
    TRISEbits.TRISE4 = 0;   \
    LATEbits.LATE4 = 0;     \
}

#define SERVO_5 LATEbits.LATE5
#define init_SERVO_5()      \
{                           \
    TRISEbits.TRISE5 = 0;   \
    LATEbits.LATE5 = 0;     \
}

#define SERVO_6 LATEbits.LATE6
#define init_SERVO_6()      \
{                           \
    TRISEbits.TRISE6 = 0;   \
    LATEbits.LATE6 = 0;     \
}

#define SERVO_7 LATEbits.LATE7
#define init_SERVO_7()      \
{                           \
    TRISEbits.TRISE7 = 0;   \
    LATEbits.LATE7 = 0;     \
}

#define init_Servos()       \
{                           \
    init_SERVO_0()          \
    init_SERVO_1()          \
    init_SERVO_2()          \
    init_SERVO_3()          \
    init_SERVO_4()          \
    init_SERVO_5()          \
    init_SERVO_6()          \
    init_SERVO_7()          \
}

#define SW_0 PORTGbits.RG6
#define init_SW_0()         \
{                           \
    TRISGbits.TRISG6 = 1;   \
}

#define SW_1 PORTGbits.RG7
#define init_SW_1()         \
{                           \
    TRISGbits.TRISG7 = 1;   \
}

#define SW_2 PORTGbits.RG8
#define init_SW_2()         \
{                           \
    TRISGbits.TRISG8 = 1;   \
}

#define SW_3 PORTGbits.RG9
#define init_SW_3()         \
{                           \
    TRISGbits.TRISG9 = 1;   \
}

#define SW_4 PORTEbits.RE8
#define init_SW_4()         \
{                           \
    TRISEbits.TRISE8 = 1;   \
}

#define SW_5 PORTEbits.RE9
#define init_SW_5()         \
{                           \
    TRISEbits.TRISE9 = 1;   \
}

#define init_SW()           \
{                           \
    init_SW_0();            \
    init_SW_1();            \
    init_SW_2();            \
    init_SW_3();            \
    init_SW_4();            \
    init_SW_5();            \
}

#define BT_FACTORYDEFAULT
#define BT_STATUS_1
#define BT_STATUS_2
#define BT_RESET

#define GPS_STATUS
#define GPS_RESET

#define init_ANALOG_BATT_MONITOR()  \
{                                   \
    TRISBbits.TRISB2 = 1;           \
}

#define init_ANALOG_DIST_0()        \
{                                   \
    TRISBbits.TRISB9 = 1;           \
}

#define init_ANALOG_DIST_1()        \
{                                   \
    TRISBbits.TRISB10 = 1;          \
}

#define init_ANALOG_DIST_2()        \
{                                   \
    TRISBbits.TRISB11 = 1;          \
}

#define init_ANALOG_DIST_3()        \
{                                   \
    TRISBbits.TRISB12 = 1;          \
}

#define init_ANALOG_STEER_SENSE()   \
{                                   \
    TRISBbits.TRISB13 = 1;          \
}

#define init_hardware_pins()    \
{                               \
    init_LEDs()                 \
    init_SW()                   \
    init_Servos()               \
    init_ANALOG_BATT_MONITOR()  \
    init_ANALOG_STEER_SENSE()   \
    init_ANALOG_DIST_0()        \
    init_ANALOG_DIST_1()        \
    init_ANALOG_DIST_2()        \
    init_ANALOG_DIST_3()        \
}

#ifdef	__cplusplus
}
#endif

#endif	/* HARDWARE_CONFIG_H */

