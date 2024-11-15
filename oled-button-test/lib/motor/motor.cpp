#include "motor.hpp"

#define motor_left_A1 17
#define motor_left_A2 18
#define motor_right_B1 38
#define motor_right_B2 37

const u8_t left_motor_foward_pin = 17;
const u8_t left_motor_backward_pin = 18;
const u8_t right_motor_foward_pin = 12;
const u8_t right_motor_backward_pin = 13;

void motor_setup() {
    pinMode(motor_left_A1, OUTPUT);
    pinMode(motor_left_A2, OUTPUT);
    pinMode(motor_right_B1, OUTPUT);
    pinMode(motor_right_B2, OUTPUT);
    digitalWrite(motor_left_A1, LOW);
    digitalWrite(motor_left_A2, LOW);
    digitalWrite(motor_right_B1, LOW);
    digitalWrite(motor_right_B2, LOW);
}
void motor_control(uint8_t lspeed, uint8_t rspeed) {
if(lspeed < 0) {
  digitalWrite(motor_left_A1, LOW);
  analogWrite(motor_left_A2, -lspeed);
} else if(lspeed > 0) {
  analogWrite(motor_left_A1, lspeed);
  digitalWrite(motor_left_A2, LOW);
} else {
  digitalWrite(motor_left_A1, LOW);
  digitalWrite(motor_left_A2, LOW);
}
if(rspeed < 0) {
  digitalWrite(motor_right_B1, LOW);
  analogWrite(motor_right_B2, -rspeed);
} else if(rspeed > 0) {
  analogWrite(motor_right_B1, rspeed);
  digitalWrite(motor_right_B2, LOW);
} else {
  digitalWrite(motor_right_B1, LOW);
  digitalWrite(motor_right_B2, LOW);
}
}