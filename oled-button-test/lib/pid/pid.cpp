#include "pid.hpp"
sensor_data sensorData;

float lspeed, rspeed;
const uint8_t basespeed = 200;
float left_error = 0;
float last_left_error = 0;
float front_error = 0;
float right_error = 0, last_right_error = 0;
float last_front_left_error = 0;
float last_front_right_error = 0;

void left_run_PD(float Kp, float Kd) {
  left_error = 3400 - sensorData.left;
  float P = Kp * left_error;
  float D = Kd * (left_error - last_left_error);
  last_left_error = left_error;
  float speed_change = P + D;
  if(speed_change > 255) speed_change = 255;
  if(speed_change < -255) speed_change = -255;
  lspeed = basespeed - speed_change;
  rspeed = basespeed + speed_change;
  motor_control(lspeed, rspeed);
  Serial.print("lspeed: " + String(lspeed) + "rspeed: " + String(rspeed));
}
void right_run_PD(float Kp, float Kd) {
    right_error = 3400 - sensorData.right;
    float P = Kp * right_error;
    float D = Kd * (right_error - last_right_error);
    last_right_error = right_error;
    float speed_change = P + D;
    if(speed_change > 255) speed_change = 255;
    if(speed_change < -255) speed_change = -255;
    lspeed = basespeed - speed_change;
    rspeed = basespeed + speed_change;
    motor_control(lspeed, rspeed);
    Serial.print("lspeed: " + String(lspeed) + "rspeed: " + String(rspeed));
}

void turn_right() {
  if(sensorData.right < 2900 && sensorData.straight_right > 3400) {
    lspeed = 250;
    rspeed = 100;
    motor_control(lspeed, rspeed);
    Serial.print("lspeed: " + String(lspeed) + "rspeed: " + String(rspeed));
  }
}
void turn_left() {
  if(sensorData.left < 2900 && sensorData.straight_right > 3400) {
    lspeed = 100;
    rspeed = 250;
    motor_control(lspeed, rspeed);
    Serial.print("lspeed: " + String(lspeed) + "rspeed: " + String(rspeed));
  }
}

