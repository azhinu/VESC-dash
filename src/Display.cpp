#include "Display.h"

/* Declare LCD object for SPI
 Adafruit_PCD8544(CLK,DIN,D/C,CE,RST); */
Adafruit_PCD8544 oled = Adafruit_PCD8544(18, 21, 4, 5, 14);

// Calculate the estimated value with Kalman Filter
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

  /* Initialize the Display*/
  oled.begin();
  // Display size is 84 x 48 pixels
  oled.setContrast(60); // Set contrast
  oled.clearDisplay(); // Clear framebuffer
  
  /* Now let us display some text */
  oled.setTextColor(WHITE, BLACK);
  oled.setCursor(0,8);
  oled.setTextSize(2);
  oled.println("   VESC  DASH ");
  oled.setTextColor(BLACK);
  oled.display();
  delay(2000);

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
  
  // Set 99% as the maximum value to avoid digit overlap.
  if (batpercentage > 100) batpercentage = 99;


  // Draw data
  
  oled.clearDisplay(); // Clear framebuffer
  // Speed value
  oled.setCursor(0,1);
  oled.setTextSize(2);
  oled.println(velocity);
  oled.setTextSize(1);
  oled.setCursor(25,1);
  oled.println("km/h");
  // Power value
  oled.setCursor(0,28);
  oled.setTextSize(2);
  oled.println(power);
  oled.setCursor(48,28);
  oled.setTextSize(1);
  oled.println("W");
  // Battery percentage
  oled.setCursor(54,1);
  oled.setTextSize(2);
  oled.println(batpercentage);
  oled.setCursor(78,1);
  oled.setTextSize(1);
  oled.println("%");
  // Battery voltage
  oled.setCursor(54,28);
  oled.setTextSize(2);
  oled.println(voltage);
  oled.setCursor(78,28);
  oled.setTextSize(1);
  oled.println("v");


  oled.display(); // Apply framebuffer
}

void Display::loop(VescUart UART) {
  
  // Check if UART available
 if ( UART.getVescValues() ) {
  // Clear screen and reset flag if UART error occured
  if (dataErr){
    oled.clearDisplay();
    oled.display();
    dataErr = false;
  }
  draw(UART);
  } else {
  dataErr = true; // Set flag if UART error occured
  oled.clearDisplay();
  oled.setCursor(0,16);
  oled.setTextSize(2);
  oled.println("No data");
  oled.display();
  }
}
