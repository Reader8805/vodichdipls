#include "sensor.hpp"

#define RightWall 1
#define RightFoward 2
#define LeftWall 15
#define LeftFoward 16
sensor_data sdata;

void sensor_read() {
  sdata.left = analogRead(LeftWall);
  //sdata.straight_left = analogRead(LeftFoward);
  sdata.right = analogRead(RightWall);
  sdata.straight_right = analogRead(RightFoward);
  Serial.print("Left wall: " + String(sdata.left) + "\n");
  Serial.print("Right wall: " + String(sdata.right) + "\n");
  // Serial.print("Left foward wall: " + String(sdata.straight_left) + "\n");
  Serial.print("Right foward wall: " + String(sdata.straight_right) + "\n");
}