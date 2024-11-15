#pragma once
#include <Arduino.h>
#include "sensor.hpp"
#include "motor.hpp"

void left_run_PD(float Kp, float Kd);
void right_run_PD(float Kp, float Kd);
void turn_right();
void turn_left();