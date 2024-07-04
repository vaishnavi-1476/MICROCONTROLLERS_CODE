#include <Wire.h>
#include <PS4Controller.h>
#define SLAVE_ADDER 9
#define ANS_SIZE 5
// #include <analogWrite.h>

int pwm = 0;

//int m11 = 25;  //rpwm1
//int m12 = 32;  //lpwm1
//int m21 = 19;  //rpwm2
//int m22 = 4;   //lpwm2
//int m31 = 18;  //rpwm3
//int m32 = 5;   //lpwm3
//int m41 = 33;  //rpwm4
//int m42 = 26;  //lpwm4

void setup() {
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(m31, OUTPUT);
  pinMode(m32, OUTPUT);
  pinMode(m41, OUTPUT);
  pinMode(m42, OUTPUT);

  PS4.begin("1a:2b:3c:11:11:11");
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  // Send character to Arduino Mega (slave)
  Wire.beginTransmission(SLAVE_ADDER);
  // Address of the Arduino Mega (slave)

  if (PS4.Triangle()) {
    Wire.write('f');
    Serial.println('f');
  }else if (PS4.Square()) {
    Wire.write('l');
    Serial.println('l');
  } else if (PS4.Circle()) {
    Wire.write('r');
    Serial.println('r');
  } else if (PS4.Cross()) {
    Wire.write('b');
    Serial.println('b');
  } else if (PS4.Touchpad()) {
    Wire.write('k');
    Serial.println('k');
  } else if (PS4.Up()) {
    Serial.println("up");
    Wire.write('u');

  } else if (PS4.Down()) {
    Serial.println("D");
    Wire.write('d');

  }
  else if (PS4.L1()) {
    Serial.println("a");
    Wire.write('a');

  }
  else if (PS4.R1()) {
    Serial.println("A");
    Wire.write('A');

  }
   else if (PS4.Left()) {
    Serial.println("B");
    Wire.write('B');

  }
   else {
    Wire.write('k');
    Serial.println('k');
  }



  Wire.endTransmission();
}
