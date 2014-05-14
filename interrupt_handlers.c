#include <p24Fxxxx.h>
#include <stdbool.h>

extern void interrupt_handler_timer1(void);
extern void uckernel_tick_handler(void);

extern void interrupt_handler_u1tx(void);
extern void interrupt_handler_u1rx(void);
extern void interrupt_handler_u2tx(void);
extern void interrupt_handler_u2rx(void);
extern void interrupt_handler_u3tx(void);
extern void interrupt_handler_u3rx(void);
extern void interrupt_handler_u4tx(void);
extern void interrupt_handler_u4rx(void);

void __attribute__((__interrupt__, auto_psv )) _ISR _OscillatorFail (void)
{
    INTCON1bits.OSCFAIL = 0;

    while(true);
}
void __attribute__((__interrupt__, auto_psv )) _ISR _AddressError (void)
{
    INTCON1bits.ADDRERR = 0;

    while(true);
}
void __attribute__((__interrupt__, auto_psv )) _ISR _StackError (void)
{
    INTCON1bits.STKERR = 0;

    while(true);
}
void __attribute__((__interrupt__, auto_psv )) _ISR _MathError (void)
{
    INTCON1bits.MATHERR = 0;

    while(true);
}

void __attribute__((__interrupt__, auto_psv )) _ISR _T1Interrupt (void)
{
    IFS0bits.T1IF = 0;
    uckernel_tick_handler();
    interrupt_handler_timer1();
}

void __attribute__((__interrupt__, auto_psv )) _ISR _T2Interrupt (void)
{
    IFS0bits.T2IF = 0;
}

void __attribute__((__interrupt__, auto_psv )) _ISR _U1TXInterrupt (void)
{
    bool result;
    IFS0bits.U1TXIF = 0;
    uart_tx_callback(0,NULL,0);
}

void __attribute__((__interrupt__, auto_psv )) _ISR _U1RXInterrupt (void)
{
    IFS0bits.U1RXIF = 0;
}

void __attribute__((__interrupt__, auto_psv )) _ISR _U2TXInterrupt (void)
{
    IFS1bits.U2TXIF = 0;
}

void __attribute__((__interrupt__, auto_psv )) _ISR _U2RXInterrupt (void)
{
    IFS1bits.U2RXIF = 0;
}

void __attribute__((__interrupt__, auto_psv )) _ISR _U3TXInterrupt (void)
{
    IFS5bits.U3TXIF = 0;
}

void __attribute__((__interrupt__, auto_psv )) _ISR _U3RXInterrupt (void)
{
    IFS5bits.U3RXIF = 0;
}

void __attribute__((__interrupt__, auto_psv )) _ISR _U4TXInterrupt (void)
{
    IFS5bits.U4TXIF = 0;
}

void __attribute__((__interrupt__, auto_psv )) _ISR _U4RXInterrupt (void)
{
    IFS5bits.U4RXIF = 0;
}
