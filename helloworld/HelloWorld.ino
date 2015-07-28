// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <DHT.h> // DHT temp humidity library
// #include "DHT.h"

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define DHTPIN 11 // Signal pin of the DHT-11
#define DHTTYPE DHT11   // DHT 11 sensor in use

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup(void) {
  Serial.begin(9600);
  //  Serial.println(F("TFT LCD test"));
  dht.begin(); // Get comms going to DHT
  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
}

void loop(void) {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    // All this "#S|ALLLOG|[]" stuff is sent back to the PC or laptop
    // to trigger a piece of software called "Gobetwino" which allows
    // you to perform a few functions on the PC and send data back to
    // the Arduino if you need to.
    Serial.print("#S|ALLLOG|[");
    Serial.print("Failed to read from DHT sensor!");
    Serial.println("]#");
    delay(6000);
  }
  else {
    Serial.print("#S|ALLLOG|[");
    Serial.print("  T: ");
    Serial.print(t);
    Serial.print(" *C \t");
    Serial.print("H: ");
    Serial.print(h);
    Serial.print(" %");
    Serial.println("]#");
    // Now put it to LCD
    tft.fillScreen(BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(WHITE);  tft.setTextSize(2);
    tft.println("Temperature/humidity");
    tft.println();
    tft.setCursor(64, 32);
    tft.setTextColor(WHITE); tft.setTextSize(2);
    tft.println("(c) R Russ");
    tft.setTextColor(RED);    tft.setTextSize(5);
    tft.println();
    tft.setTextColor(RED);    tft.setTextSize(5);
    tft.print(" T:");
    tft.setTextColor(YELLOW);    tft.setTextSize(5);
    tft.println(t);
    tft.println();
    tft.setTextColor(RED);    tft.setTextSize(5);
    tft.print(" H:");
    tft.setTextColor(YELLOW);    tft.setTextSize(5);
    tft.println(h);
    tft.println();
    delay(600000);
  }
}

