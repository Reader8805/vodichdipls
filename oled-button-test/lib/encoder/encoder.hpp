#pragma once
#include <Arduino.h>
#include <encoder.hpp>


void encoder1_isr();
void encoder2_isr();
void encoder_read();
void encoder_setup();