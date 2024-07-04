
#include<PS4Controller.h>
#include <analogWrite.h>
int m11=25;
int m12=32;
int m21=19;
int m22=4;
int m31=18;
int m32=5;
int m41=33;
int m42=26;


void setup() {
  PS4.begin("1a:2b:3c:01:01:01");
  Serial.begin(9600);
 pinMode(m11,OUTPUT);
 pinMode(m12,OUTPUT);
 pinMode(m21,OUTPUT);
 pinMode(m22,OUTPUT);
 pinMode(m31,OUTPUT);
 pinMode(m32,OUTPUT);
 pinMode(m41,OUTPUT);
 pinMode(m42,OUTPUT);

}

void loop() {
  //forwad
Serial.print(PS4.R2Value());
Serial.println( PS4.L2Value());
 if(PS4.Triangle()){ 
 analogWrite(m11,100);
 analogWrite(m12,0);
 analogWrite(m21,0);
 analogWrite(m22,100);
 analogWrite(m31,0);
 analogWrite(m32,100);
  analogWrite(m41,100);
 analogWrite(m42,0);
 } 
 //backw
 else if(PS4.Cross()){
  analogWrite(m11,0);
 analogWrite(m12,100);
 analogWrite(m21,100);
 analogWrite(m22,0);
 analogWrite(m31,100);
 analogWrite(m32,0);
  analogWrite(m41,0);
 analogWrite(m42,100);
 }
 
 //left
 else if(PS4.Square()){
  analogWrite(m11,0);
 analogWrite(m12,100);
 analogWrite(m21,0);
 analogWrite(m22,100);
 analogWrite(m31,100);
 analogWrite(m32,0);
  analogWrite(m41,100);
 analogWrite(m42,0);
 }
//right
else if(PS4.Circle()){
 analogWrite(m11,100);
 analogWrite(m12,0);
 analogWrite(m21,100);
 analogWrite(m22,0);
 analogWrite(m31,0);
 analogWrite(m32,100);
  analogWrite(m41,0);
 analogWrite(m42,100);
}
else if(PS4.Up()){
 analogWrite(m11,0);
 analogWrite(m12,0);
 analogWrite(m21,0);
 analogWrite(m22,0);
 analogWrite(m31,0);
 analogWrite(m32,0);
  analogWrite(m41,0);
 analogWrite(m42,0);
}
else if(PS4.R2Value()){
  analogWrite(m11,100);
 analogWrite(m12,0);
 analogWrite(m21,100);
 analogWrite(m22,0);
 analogWrite(m31,100);
 analogWrite(m32,0);
  analogWrite(m41,100);
 analogWrite(m42,0);
}
else if(PS4.L2Value())
{
 analogWrite(m11,0);
 analogWrite(m12,100);
 analogWrite(m21,0);
 analogWrite(m22,100);
 analogWrite(m31,0);
 analogWrite(m32,100);
  analogWrite(m41,0);
 analogWrite(m42,100); 
  }
}
