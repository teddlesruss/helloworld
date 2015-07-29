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
  dht.begin(); // Get comms going to DHT
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
}

void loop(void) {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Doh!");
    tft.setCursor(64, 280);
    tft.setTextColor(WHITE); tft.setTextSize(2);
    tft.println("             ");
    tft.setCursor(64, 280);
    tft.println("Comm Err");
    delay(2000);
  }
  else {
    
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
    tft.print("T:");
    tft.setTextColor(YELLOW);    tft.setTextSize(5);
    tft.println(t);
    tft.println();
    tft.setTextColor(RED);    tft.setTextSize(5);
    tft.print("H:");
    tft.setTextColor(YELLOW);    tft.setTextSize(5);
    tft.println(h);
    tft.println();
    for(int i=0; i < 29; i++){   
        delay(1000);          
        tft.setTextColor(RED); tft.setTextSize(2);
        tft.setCursor(164, 300);
        tft.print("*");
//         tft.print(i);
        tft.println("   ");
        delay(1000);          
        tft.setTextColor(WHITE); tft.setTextSize(2);
        tft.setCursor(164, 300);
        tft.print("*");
//         tft.print(i);
        tft.println("   ");
        }
//     delay(12000);
  }
}

