#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "config.h"
#include "Arduino.h"
#include <VescUart.h>
#include <SimpleKalmanFilter.h>
#include <SPI.h>
#include <Adafruit_PCD8544.h>


class Display {
    public:
        Display();
        void init();
        void loop(VescUart UART);
};

#endif //__DISPLAY_H__
