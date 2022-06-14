// This module is based on code by SimonRafferty
// https://github.com/SimonRafferty/VESC_ESP32_Display

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "config.h"
#include "Arduino.h"
#include <VescUart.h>
#include <SimpleKalmanFilter.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

//TFT colors
#define Black 0x0000  
#define White 0xFFFF  
#define Light_Gray 0xBDF7  
#define Dark_Gray 0x7BEF  
#define Red 0xF800  
#define Yellow 0xFFE0  
#define Orange 0xFBE0  
#define Brown 0x79E0  
#define Green 0x7E0 
#define Cyan 0x7FF 
#define Blue 0x1F  
#define Pink 0xF81F  
//TFT Resolution
#define Disp_H 240
#define Disp_V 150

class Display {
    public:
        Display();
        void init();
        void loop(VescUart UART);
};

#endif //__DISPLAY_H__