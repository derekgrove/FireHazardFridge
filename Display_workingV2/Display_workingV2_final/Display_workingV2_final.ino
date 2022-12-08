// Code by Derek Grove, libraries by ada fruit for 
// graphics: (AdaFruit GFX) and Temp (DHT11/22)

// This program is intended to program an arduino nano (or any arduino I guess) and just 
// live report the temp inside the fridge via OLED with driver IC: SSD1306
// size of OLED is 128x64 pixels.

//below packages for graphics
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//below package for temperature monitoring
#include <DHT.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address;
#define DHTTYPE DHT22

//below, initialize an object (?) named "display" that is an instance of (?) Adafruit_SSD1306
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//below, same idea, initialize an object (I think an object?) named "dht" that is an instance of DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  dht.begin();                          //start dht recording? idk, have to look in the library and see what the begin function does.

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.fillScreen(0);
  welcomeScreen();

}

void loop() {
  delay(100);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Compute heat index in Celsius (isFahreheit = false)
  //float hic = dht.computeHeatIndex(t, h, false);
  //^^ pretty sure heat index is not relevant for a fridge, things inside will reach the temp measured by the sensor

  // Check if any reads failed and exit early (to try again).
  //This should, I think, behave as a saftey measure. If there is no DHT sensor to measure temp inside the fridge
  //then the pwm = 0 (needs to be added yet) and the loop resets. 
  if (isnan(h) || isnan(t)) {
    display.setCursor(0, 0);
    display.setTextColor(1);
    display.setTextSize(2);
    display.println(F("Failed to read from DHT sensor!!!!!!!!!!"));
    display.display();
    display.clearDisplay();
    //add line here to set pwm to MOSFET = 0, thus turning off the power
    return;
  }
//display yellow text at top
display.setCursor(0, 0);
  display.setTextColor(1);
  display.setTextSize(1);
  display.println(F("Live measurements    from inside fridge:"));

//display humidity with format that I want:
  display.setCursor(0, 24);
  display.setTextColor(1);
  display.setTextSize(2);
  display.print(h);
  //Where to put the percent humidity text???
  //if humidity is less than 10, it occupies 4 digits (example: [3][.][0][0]), if its 10 or greater it occupies 5 digits
  //do a check, if its 10 or greater we accomadate by giving it more room for that extra digit,
  if (h >= 10.00) {
    display.setCursor(60, 24);
    display.println(F("%Hum."));
   }
  else {
    display.setCursor(48, 24);
    display.println(F("% Hum."));
  }
//display temperature with format that I want:
  display.setCursor(0, 48);
  display.print(t);
  //same test for when temp is below 10 degrees:
  if (t >= 10.00) {
    display.setCursor(60, 48);
   }
  else {
    display.setCursor(48, 48);
    //this line above might need tweaking to get it to line up perfectly, just a couple pixels on the x value should suffice
  }
  display.cp437(true);         // Use full 256 char 'Code Page 437' font, need for access to the degree symbol
  display.write(248);          // here is that degree symbol, its the 248th character in the code page 437 font lookup table.
  display.println(F("C"));
  display.display();
  display.clearDisplay();
 }

void welcomeScreen(void) {
  //This creates the neat "boot screen" that gives me credit.
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
  delay(4000);
  display.clearDisplay();
  display.display();
}
