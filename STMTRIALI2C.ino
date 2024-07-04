#include <Wire.h>

// Motor and Encoder pin definitions
#define Encoder1chA PC1
#define Encoder1chB PC2
#define Encoder2chA PC3
#define Encoder2chB PC4
#define Encoder3chA PC5
#define Encoder3chB PC6
#define Encoder4chA PC7
#define Encoder4chB PC8
//#define M1_L_EN 7
//#define M1_R_EN 6   
//#define M2_L_EN 9U
//#define M2_R_EN 8 
//#define M3_L_EN 10
//#define M3_R_EN 11
//#define M4_L_EN 4
//#define M4_R_EN 1m

#define M1_LPWM PB0
#define M2_LPWM PB1
#define M3_LPWM PB2
#define M4_LPWM PB3
#define M1_RPWM PB6
#define M2_RPWM PB7
#define M3_RPWM PA0
#define M4_RPWM PA1

int pre_pos1=0;
int diff_pos1=0;
float distance_1=0;
int pwr1;
int pwr2;
int pwr3;
int pwr4;

int encoderticks1 = 0;
int encoderticks2 = 0;
int encoderticks3 = 0;
int encoderticks4 = 0;

float eintegral1 = 0;
float eintegral2 = 0;
float eintegral3 = 0;
float eintegral4 = 0;
unsigned long previousmillis = 0;
int interval = 1000;
float eprev1 = 0;
float eprev2 = 0;
float eprev3 = 0;
float eprev4 = 0;
int s = 0;
float kp1 = 0.1;
float kd1 = 0.01;
float ki1 = 0.1;

float kp2 = 0.1;
float kd2 = 0.01;
float ki2 = 0.1;

float kp3 = 0.1;
float kd3 = 0.01;
float ki3 = 0.1;

float kp4 = 0.1;
float kd4 = 0.01;
float ki4 = 0.1;

float receivedAngleZ = 0.0;

void setup(){
  Serial.begin(115200);
  Wire.begin(0x08); // Join I2C bus as slave with address 0x08
  Wire.onReceive(receiveEvent); // Register event

  pinMode(Encoder1chA, INPUT_PULLUP);
  pinMode(Encoder1chB, INPUT_PULLUP);
  pinMode(Encoder2chA, INPUT_PULLUP); 
  pinMode(Encoder2chB, INPUT_PULLUP);
  pinMode(Encoder3chA, INPUT_PULLUP);
  pinMode(Encoder3chB, INPUT_PULLUP);
  pinMode(Encoder4chA, INPUT_PULLUP);
  pinMode(Encoder4chB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Encoder1chA), encoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(Encoder2chA), encoder2, RISING);
  attachInterrupt(digitalPinToInterrupt(Encoder3chA), encoder3, RISING);
  attachInterrupt(digitalPinToInterrupt(Encoder4chA), encoder4, RISING);
  
//  pinMode(M1_R_EN, OUTPUT);
//  pinMode(M1_L_EN, OUTPUT);
//  pinMode(M2_R_EN, OUTPUT);
//  pinMode(M2_L_EN, OUTPUT);
//  pinMode(M3_R_EN, OUTPUT);
//  pinMode(M3_L_EN, OUTPUT);
//  pinMode(M4_R_EN, OUTPUT);
//  pinMode(M4_L_EN, OUTPUT);

  pinMode(M1_RPWM, OUTPUT);
  pinMode(M2_RPWM, OUTPUT);
  pinMode(M3_RPWM, OUTPUT);
  pinMode(M4_RPWM, OUTPUT);
  
  pinMode(M1_LPWM, OUTPUT);
  pinMode(M2_LPWM, OUTPUT);
  pinMode(M3_LPWM, OUTPUT);
  pinMode(M4_LPWM, OUTPUT);
   
//  analogWrite(M1_R_EN, 0);
//  analogWrite(M1_L_EN, 0);
//  analogWrite(M2_R_EN, 0);
//  analogWrite(M2_L_EN, 0);
//  analogWrite(M3_R_EN, 0);
//  analogWrite(M3_L_EN, 0);
//  analogWrite(M4_R_EN, 0);
//  analogWrite(M4_L_EN, 0);
}

void loop() {
  float setrpm = 100;

  unsigned long currentmillis = millis();
  float deltaT = ((float)(currentmillis - previousmillis)) / 1000;
  if (currentmillis - previousmillis >= 1000) {
    int ticks1 = encoderticks1;
    encoderticks1 = 0;
    float rpm1 = ticks1 * 0.1875;
    float e1 = setrpm - rpm1;
    float dedt1 = (e1 - eprev1) / deltaT;
    eintegral1 = eintegral1 + e1 * deltaT;
    float u1 = kp1 * e1 + kd1 * dedt1 + ki1 * eintegral1;
    
    int ticks2 = encoderticks2;
    encoderticks2 = 0;
    float rpm2 = ticks2 * 0.1875;
    float e2 = setrpm - rpm2;
    float dedt2 = (e2 - eprev2) / deltaT;
    eintegral2 = eintegral2 + e2 * deltaT;
    float u2 = kp2 * e2 + kd2 * dedt2 + ki2 * eintegral2;

    int ticks3 = encoderticks3;
    encoderticks3 = 0;
    float rpm3 = ticks3 * 0.1875;
    float e3 = setrpm - rpm3;
    float dedt3 = (e3 - eprev3) / deltaT;
    eintegral3 = eintegral3 + e3 * deltaT;
    float u3 = kp3 * e3 + kd3 * dedt3 + ki3 * eintegral3;
    
    int ticks4 = encoderticks4;
    encoderticks4 = 0;
    float rpm4 = ticks4 * 0.1875;
    float e4 = setrpm - rpm4;
    float dedt4 = (e4 - eprev4) / deltaT;
    eintegral4 = eintegral4 + e4 * deltaT;
    float u4 = kp4 * e4 + kd4 * dedt4 + ki4 * eintegral4;
    
    pwr1 = u1 + 0.5;
    pwr2 = u2 + 0.5;
    pwr3 = u3 + 0.5;
    pwr4 = u4 + 0.5;
//if(distance_1<4&&-1>receivedAngleZ>1){
//  
//  forward();
//}
//else if(distance_1<4&&-1>receivedAngleZ){
//  Serial.print("debug>>>>>>>")
//  lang();
//  }
//  else if(distance_1<4&&1<receivedAngleZ){
//  rang();
//  }else{
//    Stop();
//  }
//    analogWrite(M1_R_EN, 255);
//    analogWrite(M1_L_EN, pwr1);
//    digitalWrite(M1_RPWM, LOW);
//    digitalWrite(M1_LPWM, HIGH);
//
//    analogWrite(M2_R_EN, pwr2);
//    analogWrite(M2_L_EN, 255);
//    digitalWrite(M2_RPWM, HIGH);
//    digitalWrite(M2_LPWM, LOW);
//
//    analogWrite(M3_R_EN, 255);
//    analogWrite(M3_L_EN, pwr3);
//    digitalWrite(M3_RPWM, LOW);
//    digitalWrite(M3_LPWM, HIGH);
//
//    analogWrite(M4_L_EN, pwr4);
//    analogWrite(M4_R_EN, 255);
//    digitalWrite(M4_LPWM, HIGH);
//    digitalWrite(M4_RPWM, LOW);

    Serial.print("   setpoint ");
    Serial.print(setrpm);
    Serial.print("   motor1: ");
    Serial.print(rpm1);
    Serial.print(", ");
    Serial.print("motor2: ");    
    Serial.print(rpm2); 
    Serial.print(", ");
    Serial.print("motor3: ");
    Serial.print(rpm3);
    Serial.print(", ");
    Serial.print("motor4: ");
    Serial.println(rpm4);
    
    eprev1 = e1;
    eprev2 = e2;
    eprev3 = e3;
    eprev4 = e4;
    previousmillis = currentmillis;
  }
  Serial.print(distance_1);
  if(distance_1<4&&receivedAngleZ>-1&&receivedAngleZ<1){
  
  forward();
}

else if(distance_1<4&&-1>receivedAngleZ){
  Serial.print("debug>>>>>>>");
  lang();
  }
  else if(distance_1<4&&1<receivedAngleZ){
  rang();
  }else{
    Stop();
  }
  // Print received angleZ value
  Serial.print("Received angleZ: ");
  Serial.println(receivedAngleZ);
}

void receiveEvent(int howMany) {
  if(howMany == sizeof(receivedAngleZ)) {
    Wire.readBytes((char*)&receivedAngleZ, sizeof(receivedAngleZ));
  }
}

void encoder1() {
 
      pre_pos1=encoderticks1;
   encoderticks1++;
    diff_pos1=(encoderticks1-pre_pos1);

  distance_1= (distance_1+(diff_pos1 / 820.0));
}

void encoder2() {
  encoderticks2++;
}

void encoder3() {
  encoderticks3++;
}

void encoder4(){
  encoderticks4++;
}
void forward(){
  Serial.print("forward");
//    analogWrite(M1_R_EN, 255);
//    analogWrite(M1_L_EN, pwr1);
    digitalWrite(M1_RPWM, LOW);
    digitalWrite(M1_LPWM, HIGH);

//    analogWrite(M2_R_EN, pwr2);
//    analogWrite(M2_L_EN, 255);
    digitalWrite(M2_RPWM, HIGH);
    digitalWrite(M2_LPWM, LOW);

//    analogWrite(M3_R_EN, 255);
//    analogWrite(M3_L_EN, pwr3);
    digitalWrite(M3_RPWM, LOW);
    digitalWrite(M3_LPWM, HIGH);

//    analogWrite(M4_L_EN, pwr4);
//    analogWrite(M4_R_EN, 255);
    digitalWrite(M4_LPWM, HIGH);
    digitalWrite(M4_RPWM, LOW);
}
void rang(){
  Serial.print("rang");
//    analogWrite(M1_R_EN, pwr1);
//    analogWrite(M1_L_EN, 255);
    digitalWrite(M1_RPWM, HIGH);
    digitalWrite(M1_LPWM, LOW);

//    analogWrite(M2_R_EN, pwr2);
//    analogWrite(M2_L_EN, 255);
    digitalWrite(M2_RPWM, HIGH);
    digitalWrite(M2_LPWM, LOW);

//    analogWrite(M3_R_EN, 255);
//    analogWrite(M3_L_EN, pwr3);
    digitalWrite(M3_RPWM, LOW);
    digitalWrite(M3_LPWM, HIGH);

//    analogWrite(M4_L_EN, 255);
//    analogWrite(M4_R_EN, pwr4);
    digitalWrite(M4_LPWM, LOW);
    digitalWrite(M4_RPWM, HIGH);
}
void lang(){
  Serial.print("lang");
//    analogWrite(M1_R_EN, 255);
//    analogWrite(M1_L_EN, pwr1);
    digitalWrite(M1_RPWM, LOW);
    digitalWrite(M1_LPWM, HIGH);

//    analogWrite(M2_R_EN, 255);
//    analogWrite(M2_L_EN, pwr2);
    digitalWrite(M2_RPWM, LOW);
    digitalWrite(M2_LPWM, HIGH);

//    analogWrite(M3_R_EN, pwr3);
//    analogWrite(M3_L_EN, 255);
    digitalWrite(M3_RPWM, HIGH);
    digitalWrite(M3_LPWM, LOW);

//    analogWrite(M4_L_EN, pwr4);
//    analogWrite(M4_R_EN, 255);
    digitalWrite(M4_LPWM, HIGH);
    digitalWrite(M4_RPWM, LOW);
}
void Stop(){
  Serial.print("stop");
//    analogWrite(M1_R_EN, 255);
    digitalWrite(M1_RPWM, HIGH);
    digitalWrite(M1_LPWM, HIGH);

//    analogWrite(M2_R_EN, 255);
//    analogWrite(M2_L_EN, 255);
    digitalWrite(M2_RPWM, HIGH);
    digitalWrite(M2_LPWM, HIGH);

//    analogWrite(M3_R_EN, 255); 
//    analogWrite(M3_L_EN, 255);
    digitalWrite(M3_RPWM, HIGH);
    digitalWrite(M3_LPWM, HIGH);

//    analogWrite(M4_L_EN, 255);
//    analogWrite(M4_R_EN, 255);
    digitalWrite(M4_LPWM, HIGH);
    digitalWrite(M4_RPWM, HIGH);
}
