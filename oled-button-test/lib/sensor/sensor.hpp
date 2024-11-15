#pragma once
#include <Arduino.h>

struct sensor_data {
int left;
int right;
int straight_left;
int straight_right;
};
void sensor_read();