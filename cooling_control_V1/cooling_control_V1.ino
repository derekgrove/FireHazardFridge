//This file will eventually control the temp of the fridge (via pwm to MOSFET to Peltier)
//and it will monitor temp of the heat sink and display that on the screen
//it MUST have fail safes for if the heat sink gets too hot and/or if the fridge starts to warm up instead of cool down
//... So i guess that means it will also be monitoring temp of cooling plate inside fridge.

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, x-direction
#define SCREEN_HEIGHT 64 // OLED display height, y-direction
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C

//below, initialize an object (?) named "display" that is an instance of (?) Adafruit_SSD1306
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//data wire is plugged into digital pin 2
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);


//define variable for Duty Cycle of pwm
int dutyCycle = 25;

void setup() {
  pinMode(3, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.fillScreen(0);
  //Serial.begin(9600);
  // Start up the library
  sensors.begin();
}

//a function for displaying pwm (duty cycle) stats on the bottom of the OLED
void display_pwm_stats() {
  display.setCursor(0, 48);
  display.print("pwm=");
  display.print(dutyCycle);
}

//a function to retrieve the temperature of the 1wire and display it on the OLED
void tempCheck() {
  sensors.requestTemperatures(); // Send the command to get temperatures
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float tempC = sensors.getTempCByIndex(0);

  // Check if reading was successful
  if(tempC != DEVICE_DISCONNECTED_C) 
  {
    display.println("Heat Sink:");
    display.print(tempC);
    display.cp437(true);         // Use full 256 char 'Code Page 437' font, need for access to the degree symbol
    display.write(248);          // here is that degree symbol, its the 248th character in the code page 437 font lookup table.
    display.println(F("C"));
  } 
  else
  {
    dutyCycle = 0;
    display.clearDisplay();
    display.print("HeatSink  TempSensor ERROR!!");
    display_pwm_stats();
    //Set dutyCycle=0, make sure this actually keeps pwm at 0 so no more power is delivered to peltiers
  }
}

void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextColor(1);
  display.setTextSize(2);
 //output pwm with a Duty Cycle = dutyCycle
 //any changes to afftec pwm's duty cycle have to occur here, before the next line when it updates the pwm
  //temp check
  tempCheck();
  display_pwm_stats();
  //this command outputs the final, "compiled" image to the physical OLED
  display.display();
  //Serial.display(dutyCycle);
 


//wait 200 milliseconds
  delay(200);
}
