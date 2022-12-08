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
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address;

//below, initialize an object (?) named "display" that is an instance of (?) Adafruit_SSD1306
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);                   // start serial communications with uno
   
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.fillScreen(0);
  welcomeScreen();

}
void loop() {
  display.setCursor(0, 0);
  display.setTextColor(1);
  display.setTextSize(2);
  display.println(F("test!"));
  display.display();
 }

void welcomeScreen(void) {
  display.setCursor(0, 0);
  display.setTextColor(1);
  display.setTextSize(2);
  display.println(F("FireHazard"));
  display.setCursor(30, 16);
  display.println(F("Fridge"));
  display.setCursor(0, 32);
  display.println(F("By:"));
  display.setCursor(0, 48);
  display.println(F("DerekGrove"));
  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();
}
