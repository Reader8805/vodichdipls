#include "encoder.hpp"

#define ENCODER_1A 9 // Pin for Encoder A
#define ENCODER_1B 10 // Pin for Encoder B
#define ENCODER_2A 11
#define ENCODER_2B 12
volatile int encoder1_value = 0; // Global variable for storing the encoder position
volatile int encoder2_value = 0;
void encoder1_isr() { // Mode: change
  // Reading the current state of encoder A and B
  int A = digitalRead(ENCODER_1A);
  int B = digitalRead(ENCODER_1B);

  // If the state of A changed, it means the encoder has been rotated
  if ((A == HIGH) != (B == HIGH)) {
    encoder1_value++; //cw
  } else {
    encoder1_value--; //ccw
  }
}
void encoder2_isr() { // Mode: change
  // Reading the current state of encoder A and B
  int A = digitalRead(ENCODER_2A);
  int B = digitalRead(ENCODER_2B);

  // If the state of A changed, it means the encoder has been rotated
  if ((A == HIGH) != (B == HIGH)) {
    encoder2_value++; //cw
  } else {
    encoder2_value--; //ccw
  }
}
void encoder_read() {
  // tinh goc quay: angle = (pulsesCurrent) * 360/(RPM: so xung tren 1 vong)
  //Tinh goc quay khi quay hon 1 vong
  // int pulsesCurrenRound = encoder1_value % 700;
  Serial.print("Encoder 1 value: " + String(encoder1_value) + "\tSo vong quay: " + String(encoder1_value/700) + "\tGoc quay: " + String(((encoder1_value % 700) * 360) / 700) + "\n");
  Serial.print("Encoder 2 value: " + String(encoder2_value) + "\tSo vong quay: " + String(encoder2_value/700) + "\tGoc quay: " + String(((encoder2_value % 700) * 360) / 700) + "\n");
}

void encoder_setup() {
    pinMode(9, INPUT_PULLUP);
    pinMode(10, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    encoder1_isr();
    encoder2_isr();
    attachInterrupt(digitalPinToInterrupt(9), encoder1_isr, CHANGE);

   // Attaching the ISR to encoder 2A
    attachInterrupt(digitalPinToInterrupt(11), encoder2_isr, CHANGE);
  // Giải thích: Nếu chân encoded A có tín hiệu từ điện áp thấp chuyển sang điện áp cao(RISING) thì hàm isr sẽ được kích hoạt (Có nghĩa là thực hiện cộng xung vào biến đếm)
}