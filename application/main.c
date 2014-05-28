#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "p24Fxxxx.h"
#include "hardware_config.h"

#include "usb/usb.h"
#include "usb/usb_device_hid.h"

#include "driver/hid/app_device_custom_hid.h"
#include "driver/hid/app_led_usb_status.h"

#include "queue.h"
#include "uckernel/uckernel.h"

enum {
    TASK_EVENT_1,
    TASK_EVENT_2,
    TASK_EVENT_3,
    TASK_EVENT_4,
    TASK_EVENT_COUNT
};

void interrupt_handler_timer1(void)
{
    return;
}

static uckernel_event event_queue_task1[5];
static void task1(const uint16_t event, void * data)
{
    uckernel_post_event(task1, 0xAA, NULL, 10);
    return;
}

static uckernel_event event_queue_task2[5];
static void task2(const uint16_t event, void * data)
{
    uckernel_post_event(task2, 0xAA, NULL, 4);
    return;
}

int main(void)
{
    /* Initialize hardware */
    init_hardware_pins();
    USBDeviceInit();
    USBDeviceAttach();
    T1CONbits.TON = 1;
    IEC0bits.T1IE = 1;
    /* uckernel Initialize */
    uckernel_init();
    /* Register tasks */
    uckernel_task_register("task1", task1, event_queue_task1,
                           sizeof(event_queue_task1),
                           UCKERNEL_TASK_PRIORITY_MED);
    uckernel_task_register("task2", task2, event_queue_task2,
                           sizeof(event_queue_task2),
                           UCKERNEL_TASK_PRIORITY_MED);
    uckernel_task_register("hid_task", hid_task, hid_task_event_queue,
                           sizeof(hid_task_event_queue),
                           UCKERNEL_TASK_PRIORITY_HIGH);
    uckernel_post_event(task1, 0xAA, NULL, 0);
    uckernel_post_event(task2, 0xAA, NULL, 0);

    for(;;) {
        /* Run uckernel_event_loop */
        uckernel_event_loop();
#if defined(USB_POLLING)
        /*
         * Interrupt or polling method.  If using polling, must call this function
         * periodically.  This function will take care of processing and responding to
         * SETUP transactions (such as during the enumeration process when you first
         * plug in).  USB hosts require that USB devices should accept and process SETUP
         * packets in a timely fashion.  Therefore, when using polling, this function
         * should be called regularly (such as once every 1.8ms or faster** [see inline
         * code comments in usb_device.c for explanation when "or faster" applies])  In
         * most cases, the USBDeviceTasks() function does not take very long to execute
         * (ex: <100 instruction cycles) before it returns.
         */
        USBDeviceTasks();
#endif
    }

    return 0;
}

bool USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void * pdata,
                                     uint16_t size)
{
    switch((int)event) {
        case EVENT_TRANSFER:
            break;

        case EVENT_SOF:
            /* We are using the SOF as a timer to time the LED indicator.  Call
             * the LED update function here. */
            APP_LEDUpdateUSBStatus();
            break;

        case EVENT_SUSPEND:
            /* Update the LED status for the suspend event. */
            APP_LEDUpdateUSBStatus();
            break;

        case EVENT_RESUME:
            /* Update the LED status for the resume event. */
            APP_LEDUpdateUSBStatus();
            break;

        case EVENT_CONFIGURED:
            /* When the device is configured, we can (re)initialize the demo
             * code. */
            APP_DeviceCustomHIDInitialize();
            break;

        case EVENT_SET_DESCRIPTOR:
            break;

        case EVENT_EP0_REQUEST:
            /* We have received a non-standard USB request.  The HID driver
             * needs to check to see if the request was for it. */
            USBCheckHIDRequest();
            break;

        case EVENT_BUS_ERROR:
            break;

        case EVENT_TRANSFER_TERMINATED:
            break;

        default:
            break;
    }

    return true;
}
