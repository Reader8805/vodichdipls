#pragma once
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels
#define OLED_RESET    -1  // Reset pin (or -1 if sharing Arduino reset pin)
#define SDA_PIN 47        // Custom SDA pin for OLED
#define SCL_PIN 48        // Custom SCL pin for OLED

class OLEDDisplay {
public:
    OLEDDisplay();
    void begin();
    void displayCurrentModeValue(bool mode, int value);
    void displayResultList(String resultList);
    void clear();
    
private:
    Adafruit_SSD1306 display;
};