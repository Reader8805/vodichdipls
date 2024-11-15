#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>

void displayCurrentModeValue();
void saveAndResetCurrentModeValue();
void updateCurrentModeValue(bool increase);
void button_setup();
void button_read();
