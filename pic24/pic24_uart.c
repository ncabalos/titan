#include <p24Fxxxx.h>
#include <stdint.h>

void uart_init(uint16_t module_number, uint16_t baud_rate)
{
    ;
}

void uart_start_tx(uint16_t module_number)
{
    switch(module_number){
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
    }
    
}
