#include "button.hpp"
#include "oled.hpp"
#define UP 4
#define MODE 5
#define ENTER 6

bool currentMode = 0;    // 0 for Left mode, 1 for Right mode
int leftValue = 0;       // Value in Left mode
int rightValue = 0;      // Value in Right mode
String resultList = "";  // String to store the result list for display

unsigned long lastDebounceTimeUp = 0;
unsigned long lastPressTimeUp = 0;
unsigned long lastDebounceTimeMode = 0;
unsigned long lastDebounceTimeEnter = 0;
unsigned long debounceDelay = 200;  // Increased debounce time to prevent bouncing
unsigned long doubleClickThreshold = 300;  // Max time interval for double click

OLEDDisplay oled;  

bool upButtonPressed = false;  // Track if UP was pressed once
bool doubleClickDetected = false;  // Track if a double-click is detected
void displayCurrentModeValue() {
    Serial.print("Current Mode: ");
  if (currentMode == 0) {
    Serial.print("L");
    Serial.println(leftValue);
    oled.displayCurrentModeValue(0, leftValue);
  } else {
    Serial.print("R");
    Serial.println(rightValue);
    oled.displayCurrentModeValue(1, rightValue);
  }
}

// Function to save the current mode and value to the result list and reset the value
void saveAndResetCurrentModeValue() {
  if (currentMode == 0) {
    resultList += "L" + String(leftValue) + " ";
    leftValue = 0;  // Reset Left value
  } else {
    resultList += "R" + String(rightValue) + " ";
    rightValue = 0;  // Reset Right value
  }

  // Display the full result list in one line
  Serial.println("Result List: " + resultList);
  oled.displayResultList(resultList);
}

// Function to increase or decrease the current mode value
void updateCurrentModeValue(bool increase) {
  if (currentMode == 0) {
    leftValue += increase ? 1 : -1;
  } else {
    rightValue += increase ? 1 : -1;
  }
  displayCurrentModeValue();
}
void button_setup() {
    pinMode(UP, INPUT_PULLUP);
    pinMode(MODE, INPUT_PULLUP);
    pinMode(ENTER, INPUT_PULLUP);
    oled.begin();
    displayCurrentModeValue();
}

void button_read() {
    unsigned long currentTime = millis();

  // Check the Mode button
  if (digitalRead(MODE) == LOW && (currentTime - lastDebounceTimeMode > debounceDelay)) {
    currentMode = !currentMode;  // Toggle between 0 (Left) and 1 (Right)
    lastDebounceTimeMode = currentTime;
    displayCurrentModeValue();
  }

  // Check the Up button
  if (digitalRead(UP) == LOW) {
    if ((currentTime - lastDebounceTimeUp) > debounceDelay) {
      // If this is the first press, start counting time for double-click
      if (!upButtonPressed) {
        upButtonPressed = true;
        lastPressTimeUp = currentTime;
      } 
      // If pressed again within doubleClickThreshold, it’s a double-click
      else if (upButtonPressed && (currentTime - lastPressTimeUp <= doubleClickThreshold)) {
        doubleClickDetected = true;
        updateCurrentModeValue(false);  // Decrease value on double-click
        upButtonPressed = false;  // Reset for next detection
      }
      lastDebounceTimeUp = currentTime;
    }
  } else {
    // If UP is released, check if it was a single-click
    if (upButtonPressed && (currentTime - lastPressTimeUp > doubleClickThreshold) && !doubleClickDetected) {
      updateCurrentModeValue(true);  // Increase value on single-click
      upButtonPressed = false;       // Reset for next detection
    }
    doubleClickDetected = false;     // Reset double-click detection
  }

  // Check the Enter button
  if (digitalRead(ENTER) == LOW && (currentTime - lastDebounceTimeEnter > debounceDelay)) {
    saveAndResetCurrentModeValue();  // Save and reset the current mode value
    lastDebounceTimeEnter = currentTime;
  }
}