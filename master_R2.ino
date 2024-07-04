#include <Wire.h>
#include<PS4Controller.h>
#define SLAVE_ADDER 9
#define ANS_SIZE 5
#include <analogWrite.h>
  
int  encoderticks1;
int  encoderticks2;
int  encoderticks3;
int  encoderticks4;
int en1a=13;
int en1b=32;
int m11=5; 
int m12=18;
int en2a=16;
int en2b=17;
int m21=25; 
int m22=27;
int en3a=34;   
int en3b=35;
int m31=26; 
int m32=33;
int en4a=15;
int en4b=23;
int m41=19; 
int m42=4;

void setup() {
pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);
pinMode(m21,OUTPUT);
pinMode(m22,OUTPUT);
pinMode(m31,OUTPUT);
pinMode(m32,OUTPUT);
pinMode(m41,OUTPUT);
pinMode(m42,OUTPUT);
pinMode(en1a,INPUT_PULLUP);
pinMode(en1b,INPUT_PULLUP);
pinMode(en2a,INPUT_PULLUP);
pinMode(en2b,INPUT_PULLUP);
pinMode(en3a,INPUT_PULLUP);
pinMode(en3b,INPUT_PULLUP);
pinMode(en4a,INPUT_PULLUP);
pinMode(en4b,INPUT_PULLUP);

attachInterrupt(digitalPinToInterrupt(en1a), encoder1 , RISING);
attachInterrupt(digitalPinToInterrupt(en2a), encoder2 , RISING);
attachInterrupt(digitalPinToInterrupt(en3a), encoder3 , RISING);
attachInterrupt(digitalPinToInterrupt(en4a), encoder4 , RISING);

  
  PS4.begin("1a:2b:3c:00:00:00");
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  
  char Stop = 'P';
  char OUT = 'O';
  char INSIDE = 'I';
  char ROLLER='R';

 
  

   if(PS4.Triangle()){
     analogWrite(m11,100);
      analogWrite(m12,0);
      analogWrite(m21,100);
      analogWrite(m22,0);
      analogWrite(m31,0);
      analogWrite(m32,100);
      analogWrite(m41,0);
      analogWrite(m42,100);
      Serial.println("Triangle is pressed");
  }
  else if(PS4.Cross()){
         analogWrite(m11,0);
      analogWrite(m12,100);
      analogWrite(m21,0);
      analogWrite(m22,100);
      analogWrite(m31,100);
      analogWrite(m32,0);
      analogWrite(m41,100);
      analogWrite(m42,0);
      Serial.println("Cross is pressed");
      
  }
else if(PS4.Square()){
     analogWrite(m11,100);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,100);
      analogWrite(m31,0);
      analogWrite(m32,100);
      analogWrite(m41,100);
      analogWrite(m42,0); 
      Serial.println("Square is pressed");  
      
  }
  else if(PS4.Circle()){
      analogWrite(m11,0);
      analogWrite(m12,100);
      analogWrite(m21,100);
      analogWrite(m22,0);
      analogWrite(m31,100);
      analogWrite(m32,0);
      analogWrite(m41,0);
      analogWrite(m42,100);
      Serial.println("Circle is pressed"); 
      
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
      Serial.println("Base motor stops");
    }
  
  // Send character to Arduino Mega (slave)
  Wire.beginTransmission(SLAVE_ADDER);  // Address of the Arduino Mega (slave)
  
  if(PS4.Touchpad())
  {
      analogWrite(m11,0);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,0);
      analogWrite(m31,0);
      analogWrite(m32,0);
      analogWrite(m41,0);
      analogWrite(m42,0);
      Wire.write(Stop); 
      Serial.println("Touchpad is pressed");
  }
  else if(PS4.Up()){
      Wire.write(OUT);
      Serial.println("Up is pressed");
  }
  else if (PS4.Down()){
     Wire.write(INSIDE);
     Serial.println("Down is pressed");
  }
    else if(PS4.Right()){
   Wire.write(ROLLER);
   
  }
 else if(PS4.Left()){
  Wire.write(Stop);
 }
  Wire.endTransmission();

  // Request character from Arduino Mega (slave)
//  Serial.println(charToSend);
//  Wire.requestFrom(SLAVE_ADDER,ANS_SIZE);  // Request 1 byte from the Arduino Mega (slave)
//  if (Wire.available()) {
//    char receivedChar = Wire.read();
//    Serial.print("Received char from Arduino Mega: ");
//    Serial.println(receivedChar);
//  }
}
void encoder1(){
  encoderticks1++;
}
void encoder2(){
  encoderticks2++;
}
void encoder3(){
  encoderticks3++;
}
void encoder4(){
  encoderticks4++;
}
