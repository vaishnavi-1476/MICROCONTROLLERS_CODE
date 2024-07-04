#include <Wire.h>
#include<PS4Controller.h>
#define SLAVE_ADDER 9
#define ANS_SIZE 5
#include <analogWrite.h>

#define enca1 23
#define encb1 14
#define enca2 17
#define encb2 13
#define enca3 16
#define encb3 27
#define enca4 15
#define encb4 2

        //   m1          m2
        //   |-----------|
        //   |           |        ___
        //   |           |-------|___    Ball pick
        //   |           |
        //   |___________|
        //    | |     | |
        //  m4           m3
        //  Seedling pick

int pwm1= 145;
int pwm2= 150;
int pwm3= 140;
int pwm4= 135;

int jpwm1 = 0;
int jpwm2 = 0;
int jpwm3 = 0;
int jpwm4 = 0;

int m11=25; //rpwm1 
int m12=32; //lpwm1
int m21=19; //rpwm2
int m22=4; //lpwm2
int m31=18; //rpwm3
int m32=5; //lpwm3  
int m41=33; //rpwm4
int m42=26; //lpwm4

volatile int encoderticks1;
volatile int encoderticks2;
volatile int encoderticks3;
volatile int encoderticks4;

void setup() {
pinMode(m11,OUTPUT);  
pinMode(m12,OUTPUT);
pinMode(m21,OUTPUT);
pinMode(m22,OUTPUT);
pinMode(m31,OUTPUT);
pinMode(m32,OUTPUT);
pinMode(m41,OUTPUT);
pinMode(m42,OUTPUT);

  pinMode(enca1,INPUT_PULLUP);
  pinMode(encb1,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(enca1),encoder1,RISING);
  pinMode(enca2,INPUT_PULLUP);
  pinMode(encb2,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(enca2),encoder2,RISING);
  pinMode(enca3,INPUT_PULLUP);
  pinMode(encb3,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(enca3),encoder3,RISING);
  pinMode(enca4,INPUT_PULLUP);
  pinMode(encb4,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(enca4),encoder4,RISING);
  
  //PS4.begin("11:11:11:11:11:11");
  PS4.begin("1a:2b:3c:00:00:00"); //Team CiPHER
  Serial.begin(9600);
  Wire.begin();
}

void loop() {

  Serial.print("   motor1: ");
  Serial.print(encoderticks1);
  Serial.print("   motor2: ");
  Serial.print(encoderticks2);
  Serial.print("   motor3: ");
  Serial.print(encoderticks3);
  Serial.print("   motor4: ");
  Serial.println(encoderticks4);
  
  // Send character to Arduino Mega (slave)
  Wire.beginTransmission(SLAVE_ADDER);  
  // Address of the Arduino Mega (slave)
  
  if(PS4.Triangle() && PS4.Circle()){
      analogWrite(m11,pwm1);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,0);
      analogWrite(m31,0);
      analogWrite(m32,pwm3);
      analogWrite(m41,0);
      analogWrite(m42,0);
      Serial.println("R_diag_fwd");
  }
   else if(PS4.Square() && PS4.Cross()){
      analogWrite(m11,0);
      analogWrite(m12,pwm1);
      analogWrite(m21,0);
      analogWrite(m22,0);
      analogWrite(m31,pwm3);
      analogWrite(m32,0);
      analogWrite(m41,0);
      analogWrite(m42,0);
       Serial.println("R_diag_bwd");
  }
  else if(PS4.Triangle() && PS4.Square()){
      analogWrite(m11,0);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,pwm2);
      analogWrite(m31,0);
      analogWrite(m32,0);
      analogWrite(m41,pwm4);
      analogWrite(m42,0);
       Serial.println("L_diag_fwd");
  }
else if(PS4.Cross() && PS4.Circle()){
      analogWrite(m11,0);
      analogWrite(m12,0);
      analogWrite(m21,pwm2);
      analogWrite(m22,0);
      analogWrite(m31,0);
      analogWrite(m32,0);
      analogWrite(m41,0);
      analogWrite(m42,pwm4);
       Serial.println("L_diag_bwd");
  }
 else if(PS4.Triangle()){
      analogWrite(m11,pwm1);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,pwm2);
      analogWrite(m31,0);
      analogWrite(m32,pwm3);
      analogWrite(m41,pwm4);
      analogWrite(m42,0);
      Serial.println('F');
  }
  else if(PS4.RStickY() > 10)
  {
    jpwm1 = map(PS4.RStickY() , 10 , 127  , 0 , pwm1);
    jpwm2 = map(PS4.RStickY() , 10 , 127  , 0 , pwm2);
    jpwm3 = map(PS4.RStickY() , 10 , 127  , 0 , pwm3);
    jpwm4 = map(PS4.RStickY() , 10 , 127  , 0 , pwm4);
    analogWrite(m11,jpwm1);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,jpwm2);
      analogWrite(m31,0);
      analogWrite(m32,jpwm3);
      analogWrite(m41,jpwm4);
      analogWrite(m42,0);
      Serial.println('F');
    }
  else if(PS4.Cross()){
      analogWrite(m11,0);
      analogWrite(m12,pwm1);
      analogWrite(m21,pwm2);
      analogWrite(m22,0);
      analogWrite(m31,pwm3);
      analogWrite(m32,0);
      analogWrite(m41,0);
      analogWrite(m42,pwm4);
      Serial.println('B');  
  }
  else if(PS4.RStickY() < -10)
  {
    jpwm1 = map(PS4.RStickY() , -10 , -127  , 0 , pwm1);
    jpwm2 = map(PS4.RStickY() , -10 , -127  , 0 , pwm2);
    jpwm3 = map(PS4.RStickY() , -10 , -127  , 0 , pwm3);
    jpwm4 = map(PS4.RStickY() , -10 , -127  , 0 , pwm4);
     analogWrite(m11,0);
      analogWrite(m12,jpwm1);
      analogWrite(m21,jpwm2);
      analogWrite(m22,0);
      analogWrite(m31,jpwm3);
      analogWrite(m32,0);
      analogWrite(m41,0);
      analogWrite(m42,jpwm4);
      Serial.println('B'); 
    }
  else if (PS4.Square()){
      analogWrite(m11,0);
      analogWrite(m12,pwm1);
      analogWrite(m21,0);
      analogWrite(m22,pwm2);
      analogWrite(m31,pwm3);
      analogWrite(m32,0);
      analogWrite(m41,pwm4);
      analogWrite(m42,0);
      Serial.println('L');  
  }
  else if(PS4.RStickX() < -10)
  {
    jpwm1 = map(PS4.RStickX() , -10 , -127  , 0 , pwm1);
    jpwm2 = map(PS4.RStickX() , -10 , -127  , 0 , pwm2);
    jpwm3 = map(PS4.RStickX() , -10 , -127  , 0 , pwm3);
    jpwm4 = map(PS4.RStickX() , -10 , -127  , 0 , pwm4); 
      analogWrite(m11,0);
      analogWrite(m12,jpwm1);
      analogWrite(m21,0);
      analogWrite(m22,jpwm2);
      analogWrite(m31,jpwm3);
      analogWrite(m32,0);
      analogWrite(m41,jpwm4);
      analogWrite(m42,0);
      Serial.println('L');
    }
  else if(PS4.Circle()){
      analogWrite(m11,pwm1);
      analogWrite(m12,0);
      analogWrite(m21,pwm2);
      analogWrite(m22,0);
      analogWrite(m31,0);
      analogWrite(m32,pwm3);
      analogWrite(m41,0);
      analogWrite(m42,pwm4);
      Serial.println('R');
  }
  else if(PS4.RStickX() > 10)
  {
    jpwm1 = map(PS4.RStickX() , 10 , 127  , 0 , pwm1);
    jpwm2 = map(PS4.RStickX() , 10 , 127  , 0 , pwm2);
    jpwm3 = map(PS4.RStickX() , 10 , 127  , 0 , pwm3);
    jpwm4 = map(PS4.RStickX() , 10 , 127  , 0 , pwm4);
    analogWrite(m11,jpwm1);
      analogWrite(m12,0);
      analogWrite(m21,jpwm2);
      analogWrite(m22,0);
      analogWrite(m31,0);
      analogWrite(m32,jpwm3);
      analogWrite(m41,0);
      analogWrite(m42,jpwm4);
      Serial.println('R');
    }
    else if(PS4.L2()){
      analogWrite(m11,75);
      analogWrite(m12,0);
      analogWrite(m21,75);
      analogWrite(m22,0);
      analogWrite(m31,75);
      analogWrite(m32,0);
      analogWrite(m41,75);
      analogWrite(m42,0);
      Serial.println("L2");
  }
    else if(PS4.R2()){
      analogWrite(m11,0);
      analogWrite(m12,75);
      analogWrite(m21,0);
      analogWrite(m22,75);
      analogWrite(m31,0);
      analogWrite(m32,75);
      analogWrite(m41,0);
      analogWrite(m42,75);
      Serial.println("R2");
  }
else if(PS4.Touchpad())
  {
      analogWrite(m11,0);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,0);
      analogWrite(m31,0);
      analogWrite(m32,0);
      analogWrite(m41,0);
      analogWrite(m42,0);
      Wire.write('P'); 
      Serial.println("stop touchpad");
  }
  else
  {
      analogWrite(m11,0);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,0);
      analogWrite(m31,0);
      analogWrite(m32,0);
      analogWrite(m41,0);
      analogWrite(m42,0);
//      analogWrite(m11,255);
//      analogWrite(m12,255);
//      analogWrite(m21,255);
//      analogWrite(m22,255);
//      analogWrite(m31,255);
//      analogWrite(m32,255);
//      analogWrite(m41,255);
//      analogWrite(m42,255);
      Serial.println("stop else");
  }

  if(PS4.Up()){
    Serial.println("up");
      Wire.write('U');
      
  }
  else if (PS4.Down()){
     Wire.write('D');
     Serial.println("down");
  }
//  else if (PS4.Left()){
//     Wire.write('C');
//     Serial.println("close1");
//  }
//   else if (PS4.L1()){
//     Wire.write('O');
//     Serial.println("open1");
//  }
   else if (PS4.L1()){
     Wire.write('X');
     Serial.println("ball throwing");
  }
   else if (PS4.Right()){
     Wire.write('o');
     Serial.println("close2");
  }
   else if (PS4.R1()){
     Wire.write('c');
     Serial.println("open2");
  } 
  else if(PS4.Touchpad())
  {
      Wire.write('P'); 
      Serial.println("stop touchpad");
  }
 else if (PS4.Share()){
     Wire.write('S');
     Serial.println("shoot");
  }
   else if (PS4.Options()){
     Wire.write('B');
     Serial.println("back");
  }
  else if(PS4.LStickY() >= 20)
  {
      Wire.write('A'); 
        Serial.println("angle_motor_up");
    }

     else if(PS4.LStickY() <=  -20)
  {
      Wire.write('a'); 
        Serial.println("angle_motor_down");
    }

  else
  {
      Wire.write('Z'); 
      Serial.println("stop else");   
  }
 Wire.endTransmission();
}

void encoder1()
{
  int en1b=digitalRead(encb1);
  if(en1b>0)
  {
    encoderticks1++;
  }
  else
  {
    encoderticks1--;
  }
}
void encoder2()
{
  int en2b=digitalRead(encb2);
  if(en2b>0)
  {
    encoderticks2++;
  }
  else
  {
    encoderticks2--;
  }
}
void encoder3()
{
  int en3b=digitalRead(encb3);
  if(en3b>0)
  {
    encoderticks3++;
  }
  else
  {
    encoderticks3--;
  }
}
 void encoder4()
{
  int en4b=digitalRead(encb4);
  if(en4b>0)
  {
    encoderticks4++;
  }
  else
  {
    encoderticks4--;
  }
}
