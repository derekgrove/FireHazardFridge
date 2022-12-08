// Code by Derek Grove, libraries by ada fruit for 
// graphics (AdaFruit GFX) and Temp (DHT11/22)

//below packages for graphics
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS_1 0x3C ///< See datasheet for Address;
//#define SCREEN_ADDRESS_2 0x

//below, initialize an object (?) named "display" that is an instance of (?) Adafruit_SSD1306
Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);                   // start serial communications with uno
   
  display1.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS_1);
  display1.fillScreen(0);
  welcomeScreen();

}
void loop() {
  display1.setCursor(0, 0);
  display1.setTextColor(1);
  display1.setTextSize(2);
  display1.println(F("test!"));
  display1.display();
 }

void welcomeScreen(void) {
  display1.setCursor(0, 0);
  display1.setTextColor(1);
  display1.setTextSize(2);
  display1.println(F("FireHazard"));
  display1.setCursor(30, 16);
  display1.println(F("Fridge"));
  display1.setCursor(0, 32);
  display1.println(F("By:"));
  display1.setCursor(0, 48);
  display1.println(F("DerekGrove"));
  display1.display();
  delay(3000);
  display1.clearDisplay();
  display1.display();
}
