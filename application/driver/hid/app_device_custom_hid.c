/********************************************************************
 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *******************************************************************/

/** INCLUDES *******************************************************/
#include "../../usb/usb.h"
#include "../../usb/usb_device_hid.h"

#include "../../uckernel/uckernel.h"

#include <string.h>

uint8_t hid_rx_buffer[64];
uint8_t hid_tx_buffer[64];

volatile USB_HANDLE USBOutHandle;
volatile USB_HANDLE USBInHandle;

/** DEFINITIONS ****************************************************/
typedef enum {
    COMMAND_TOGGLE_LED = 0x80,
    COMMAND_GET_BUTTON_STATUS = 0x81,
    COMMAND_READ_POTENTIOMETER = 0x37
} CUSTOM_HID_DEMO_COMMANDS;

/** FUNCTIONS ******************************************************/

/*********************************************************************
* Function: void APP_DeviceCustomHIDInitialize(void);
*
* Overview: Initializes the Custom HID demo code
*
* PreCondition: None
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDInitialize()
{
    /* initialize the variable holding the handle for the last */
    /* transmission */
    USBInHandle = 0;
    /* enable the HID endpoint */
    USBEnableEndpoint(TITANCONTROLLER_HID_EP,
                      USB_IN_ENABLED | USB_OUT_ENABLED | USB_HANDSHAKE_ENABLED | USB_DISALLOW_SETUP);
    /* Re-arm the OUT endpoint for the next packet */
    USBOutHandle = (volatile USB_HANDLE)HIDRxPacket(TITANCONTROLLER_HID_EP,
                   (uint8_t *)&hid_rx_buffer, 64);
}

void hid_task(const uint16_t event, void * data)
{
    /* Check if we have received an OUT data packet from the host */
    if(HIDRxHandleBusy(USBOutHandle) == false) {
        /* We just received a packet of data from the USB host. */
        /* Check the first uint8_t of the packet to see what command the host */
        /* application software wants us to fulfill. */
        switch(hid_rx_buffer[0]) {			/* Look at the data the host sent, to see what kind of application specific command it sent. */
            case COMMAND_TOGGLE_LED:  /* Toggle LEDs command */
                /* LED_Toggle(LED_USB_DEVICE_HID_CUSTOM); */
                break;

            case COMMAND_GET_BUTTON_STATUS:  /* Get push button state */

                /* Check to make sure the endpoint/buffer is free before we modify the contents */
                if(!HIDTxHandleBusy(USBInHandle)) {
                    hid_tx_buffer[0] = 0x81;
                    /* Prepare the USB module to send the data packet to the host */
                    USBInHandle = HIDTxPacket(TITANCONTROLLER_HID_EP, (uint8_t *)&hid_tx_buffer[0],
                                              64);
                }

                break;

            case COMMAND_READ_POTENTIOMETER: {
                /* Read POT command.  Uses ADC to measure an analog voltage on one of the ANxx I/O pins, and returns the result to the host */
                uint16_t pot;

                /* Check to make sure the endpoint/buffer is free before we modify the contents */
                if(!HIDTxHandleBusy(USBInHandle)) {
                    /* Use ADC to read the I/O pin voltage.  See the relevant HardwareProfile - xxxxx.h file for the I/O pin that it will measure. */
                    /* Some demo boards, like the PIC18F87J50 FS USB Plug-In Module board, do not have a potentiometer (when used stand alone). */
                    /* This function call will still measure the analog voltage on the I/O pin however.  To make the demo more interesting, it */
                    /* is suggested that an external adjustable analog voltage should be applied to this pin. */
                    hid_tx_buffer[0] =
                        0x37;  	/* Echo back to the host the command we are fulfilling in the first uint8_t.  In this case, the Read POT (analog voltage) command. */
                    memcpy(&hid_tx_buffer[1], &pot, 2);
                    /* Prepare the USB module to send the data packet to the host */
                    USBInHandle = HIDTxPacket(TITANCONTROLLER_HID_EP, (uint8_t *)&hid_tx_buffer[0],
                                              64);
                }
            }
            break;
        }

        /* Re-arm the OUT endpoint, so we can receive the next OUT data packet */
        /* that the host may try to send us. */
        USBOutHandle = HIDRxPacket(TITANCONTROLLER_HID_EP, (uint8_t *)&hid_rx_buffer,
                                   64);
    }

    uckernel_post_event(hid_task, 0, NULL, 5);
}