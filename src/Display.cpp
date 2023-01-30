// This module is based on code by SimonRafferty
// https://github.com/SimonRafferty/VESC_ESP32_Display

#include "Display.h"

TFT_eSPI tft = TFT_eSPI();  // Initiate a display object
// calculate the estimated value with Kalman Filter
SimpleKalmanFilter PowerFilter(2, 2, 0.1); // Initiate Kalman Filter
SimpleKalmanFilter BatteryFilter(4, 4, 0.1); // Initiate Kalman Filter

// Vars
int rpm;
int velocity;
float current;
float voltage;
int power;
int batpercentage;
bool dataErr;



Display::Display() {}

void Display::init() {

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(Orange);

  //Splash Screen
  tft.drawCentreString(SplashScreenFirstLine, Disp_H/2, 10, 4);
  tft.drawCentreString(SplashScreenSecondLine, Disp_H/2, 45, 4);
  tft.setTextColor(Yellow);
  tft.drawCentreString(SplashScreenThirdLine, Disp_H/2, 90, 4);
  
  delay(3000);
  tft.fillScreen(TFT_BLACK);

#if DEBUG > 0
  Serial.println("Display init done...");
#endif 
}

void draw(VescUart UART) {
  // Read Vesc telemetry
  rpm = UART.data.rpm / (Poles / 2);                              // UART.data.rpm returns eRPM.  Divide by no of pole pairs in the motor for actual. 
  voltage = (UART.data.inpVoltage);                               // Battery Voltage
  current = (UART.data.avgInputCurrent);                          // Current Draw
  power = PowerFilter.updateEstimate(voltage*current);            // Power = Voltage x Current
  velocity = rpm*3.142*WheelDia*GearReduction*60/1000;            // Motor RPM x Pi x Wheel diameter x (motor pulley / wheelpulley) * 60 minutes in hour / 1000 meters in kilometer
  batpercentage = BatteryFilter.updateEstimate((voltage-BatteryMinVoltage)/(BatteryMaxVoltage-BatteryMinVoltage)*100); // Filtered value, based on a minimum and maximum cell charge
  
  // Adjust the below to show apparently legal values
  //if(velocity>18) velocity = 17 + (velocity / 7)  // If velocity > 18, value will be reduced
  //powerfiltered = powerfiltered / 6 //Read 0 to 250W

  // Convert to fixed leght string

  String velocitySRT;
  String powerSRT;

  if (velocity < 0) {velocitySRT = String(velocity);}
  else if (velocity < 10) {velocitySRT = String("  " + String(velocity));}
  else {velocitySRT = String(velocity);}

  if (power < -10) {powerSRT = String("0" + String(power));}
  else if (power < 0) {powerSRT = String("00" + String(power));}
  else if (power < 10) {powerSRT = String("000" + String(power));}
  else if (power < 100) {powerSRT = String("00" + String(power));}
  else if (power < 1000) {powerSRT = String("0" + String(power));}
  else {powerSRT = String(power);}
  
  // Set 99% as the maximum value to avoid stuck digit on display.
  if (batpercentage > 100) batpercentage = 99;


  // Draw data
  
  // First line  
  tft.setTextColor(Orange, Black);
  tft.drawRightString(velocitySRT, 80, 3, 7);
  tft.drawString("km/h", 85, 3, 2);

  //Change Battery Percentage colour based on value
  tft.setTextColor(Red, Black); 
  if(batpercentage>30) tft.setTextColor(Orange, Black); 
  if(batpercentage>50) tft.setTextColor(Yellow, Black); 
  if(batpercentage>80) tft.setTextColor(Green, Black); 

  tft.drawRightString(String(batpercentage), 220, 3, 7);
  tft.drawString("%", 223, 3, 2);

   
  // Second line
  tft.setTextColor(Green, Black);
  tft.drawRightString(powerSRT, 75, 80, 7);
  tft.drawString("W", 130, 80, 2);

  tft.setTextColor(Red, Black);
  tft.drawRightString(String(int(voltage)), 225, 80, 7);
  tft.drawString("V", 228, 80, 2);
}

void Display::loop(VescUart UART) {
  
  // Check if UART available
 if ( UART.getVescValues() ) {
  // Clear screen and reset flag if UART error occured
  if (dataErr){
    tft.fillScreen(TFT_BLACK);
    dataErr = false;
  }
  draw(UART);
  } else {
  dataErr = true; // Set flag if UART error occured
  tft.setTextColor(Orange, Black);
  tft.drawCentreString("No Data!", Disp_H/2, 10, 4);
  }
}
