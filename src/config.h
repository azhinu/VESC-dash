#ifndef __CONFIG_H__
#define __CONFIG_H__

// Base setup
#define BTN2 0  // BTN1 GPIO pin
#define BTN1 35 // BTN2 GPIO pin

#define VESC_BAUD_RATE 115200  // VESC UART baud rate

#define BT_NAME "ESP32"    // The name this controller should advertise for BLE
#define BUZPIN 25          // PIN for Piezo buzzer for acoustic signals (e.g. battery warning). Not implemented yet.
#define VESC_RX_PIN 15     // UART RX, connent to TX on VESC
#define VESC_TX_PIN 13     // UART TX, connent to RX on VESC
#define LIGHT_PIN 17       // PIN for the light switch

// Set mode for BTN1. Can be "1" = toggle flag on press; "2" = passthrough button
#define BTN_MODE 2

// There are two different buzzer start sequences 1==chasing, 2==cylon
#define STARTSEQUENCE 1

//Display setup
#define Poles 30                            //Usually 30 for e-scooter
#define WheelDia 0.24                      //Wheel diameter in meters. 10" tire diameter is about 0.25m
#define GearReduction 1                     //reduction ratio. 1 for direct drive. Otherwise motor pulley diameter / Wheel pulley diameter.
#define BatteryCells 13                     //Number of battery series cells
#define BatteryMinVoltage 3.2               //Minimum Battery cell Voltage
#define SplashScreenFirstLine "ESP32"       //First line of Splash Screen
#define SplashScreenSecondLine "Starting"   //Second line of Splash Screen
#define SplashScreenThirdLine "..."         //Third line of Splash Screen


#define DEBUG 0 // enable DEBUG, the higher the number, the more DEBUG output

#endif //__CONFIG_H__