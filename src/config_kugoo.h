#ifndef __CONFIG_H__
#define __CONFIG_H__

// Base setup
#define BTN1 0  // BTN1 GPIO pin
#define BTN2 35 // BTN2 GPIO pin

#define VESC_BAUD_RATE 115200  // VESC UART baud rate

#define BT_NAME "ESP32"    // The name this controller should advertise for BLE
#define VESC_RX_PIN 15     // UART RX, connent to TX on VESC
#define VESC_TX_PIN 13     // UART TX, connent to RX on VESC
#define LIGHT_PIN 17       // PIN for the light switch

// Set mode for BTN1. Can be "1" = toggle flag on press; "2" = passthrough button
#define BTN_MODE 2


//Display setup
#define Poles 30                            //Usually 30 for e-scooter
#define WheelDia 0.24                      //Wheel diameter in meters. 10" tire diameter is about 0.25m
#define GearReduction 1                     //reduction ratio. 1 for direct drive. Otherwise motor pulley diameter / Wheel pulley diameter.
#define BatteryMinVoltage 41.6              //Minimum Battery Voltage = Cell voltage min * Number of cells
#define BatteryMaxVoltage 53.3              //Maximum Battery Voltage = Cell voltage max * Number of cells


#define DEBUG 0 // enable DEBUG, the higher the number, the more DEBUG output

#endif //__CONFIG_H__
