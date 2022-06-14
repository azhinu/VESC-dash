#include <Arduino.h>
#include "config.h"
#include "BleBridge.h"
#include "Display.h"
// #include "Buzzer.h"

HardwareSerial vesc(2);              // Initiate Vesc Uart object
VescUart UART;                       // Initiate VescUart class
BleBridge *bridge = new BleBridge(); // Initiate BleBridge object
Display *display = new Display();    // Initiate Display object
// Buzzer *buzzer = new Buzzer();    // Initiate Buzzer object

bool light = true; // Light status flag
static u_int32_t last_display_update; // Display update timer
static u_int32_t last_btn_update; // Button update timer



void setup() {
#if DEBUG > 0
  Serial.begin(VESC_BAUD_RATE);
#endif

  // Set pin modes
  pinMode(LIGHT_PIN, OUTPUT);     // Set light pin to output
  digitalWrite(LIGHT_PIN, light); // Turn on light on startup
  pinMode(BTN1, INPUT);           // Set BTN1 pin to input
  pinMode(BTN2, INPUT);           // Set BTN2 pin to input

  vesc.begin(VESC_BAUD_RATE, SERIAL_8N1, VESC_RX_PIN, VESC_TX_PIN, false);  // Start UART communication    
  UART.setSerialPort(&vesc); // Set serial port to VescUart object
  
  bridge->init(&vesc); // initialize the UART bridge from VESC to Bluetooth
  display->init(); // initialize the display

  // buzzer->startSequence(); // initialize the buzzer
}

void loop() {
  
  bridge->loop(); // call the VESC UART-to-Bluetooth bridge

  // call the display once per second
  if (millis() - last_display_update > 1000) {
    #if DEBUG > 0
      Serial.println("Display loop done...");
    #endif
    display->loop(UART); // call the display update
    last_display_update = millis(); // update the last display update time
  }

  // Turn on/off the light
  if (digitalRead(BTN1) == LOW && millis() - last_btn_update > 500) {
    light = !light;
    digitalWrite(LIGHT_PIN, light);
    last_btn_update = millis();
    #if DEBUG > 0
      Serial.println("Light status now is " + String(light));
    #endif
  }
}