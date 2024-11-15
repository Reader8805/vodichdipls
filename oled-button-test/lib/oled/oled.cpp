#include "oled.hpp"

OLEDDisplay::OLEDDisplay() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

void OLEDDisplay::begin() {
    // Initialize I2C with custom SDA and SCL pins
    Wire.begin(SDA_PIN, SCL_PIN);

    // Initialize OLED display
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 allocation failed");
        for(;;); // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.setTextSize(1);          // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.display();
}

// Function to display the current mode and value on OLED
void OLEDDisplay::displayCurrentModeValue(bool mode, int value) {
    display.clearDisplay();
    display.setCursor(0, 0);

    display.print("Current Mode: ");
    if (mode == 0) {
        display.print("L");
    } else {
        display.print("R");
    }
    display.println(value);
    display.display();
}

// Function to display the result list on OLED
void OLEDDisplay::displayResultList(String resultList) {
    display.clearDisplay();
    display.setCursor(0, 0);

    display.println("Result List:");
    display.println(resultList);
    display.display();
}

// Function to clear the OLED display
void OLEDDisplay::clear() {
    display.clearDisplay();
    display.display();
}