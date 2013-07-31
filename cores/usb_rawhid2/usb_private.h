#ifndef usb_serial_h__
#define usb_serial_h__

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

/**************************************************************************
 *
 *  Configurable Options
 *
 **************************************************************************/

#define VENDOR_ID               0x16C0
#define PRODUCT_ID              0x0486
#define RAWHID_USAGE_PAGE	0xFFAB  // recommended: 0xFF00 to 0xFFFF
#define RAWHID_USAGE		0x0200  // recommended: 0x0100 to 0xFFFF

// These determine how much USB bandwidth is allocated (1=fastest)
#define RAWHID_TX_INTERVAL	1
#define RAWHID_RX_INTERVAL	1
#define DEBUG_TX_INTERVAL	1
#define DEBUG_RX_INTERVAL	1

#define TRANSMIT_FLUSH_TIMEOUT  2   /* in milliseconds */
#define TRANSMIT_TIMEOUT        5   /* in milliseconds */


/**************************************************************************
 *
 *  Endpoint Buffer Configuration
 *
 **************************************************************************/

#define STR_PRODUCT             L"Teensyduino RawHID+Joystick"
#define STR_RAWHID		L"Teensyduino RawHID+Joystick"
#define STR_DEBUG		L"Emulated Arduino Serial"
#define ENDPOINT0_SIZE          8

#define RAWHID_INTERFACE	0
#define RAWHID_TX_ENDPOINT	3
#define RAWHID_TX_BUFFER	EP_DOUBLE_BUFFER
#define RAWHID_TX_SIZE		0
#define RAWHID_RX_ENDPOINT	4
#define RAWHID_RX_BUFFER	EP_DOUBLE_BUFFER
#define RAWHID_RX_SIZE		2

#define JOYSTICK_INTERFACE	2
#define JOYSTICK_ENDPOINT	5
#define JOYSTICK_SIZE		16
#define JOYSTICK_BUFFER		EP_DOUBLE_BUFFER
#define JOYSTICK_INTERVAL	1

#define DEBUG_INTERFACE		1
#define DEBUG_TX_ENDPOINT	1
#define DEBUG_TX_SIZE		0
#define DEBUG_TX_BUFFER		EP_DOUBLE_BUFFER
#define DEBUG_RX_ENDPOINT	2
#define DEBUG_RX_SIZE		2
#define DEBUG_RX_BUFFER		EP_DOUBLE_BUFFER

#define NUM_ENDPOINTS		6
#define NUM_INTERFACE		3


// setup
void usb_init(void);			// initialize everything
void usb_shutdown(void);		// shut off USB

// variables
extern volatile uint8_t usb_configuration;
extern volatile uint8_t usb_suspended;
extern volatile uint8_t debug_flush_timer;
extern volatile uint16_t rawhid_rx_timeout_count;
extern volatile uint16_t rawhid_tx_timeout_count;
#ifdef JOYSTICK_INTERFACE
extern uint8_t joystick_report_data[12];
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif
