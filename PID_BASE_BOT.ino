#include<analogWrite.h>
#include<PS4Controller.h>
#define enc1cha 23
#define enc1chb 14
#define LPWM1 32
#define RPWM1 25

#define enc2cha 17
#define enc2chb 13
#define LPWM2 4
#define RPWM2 19

#define enc3cha 16
#define enc3chb 27
#define LPWM3 5
#define RPWM3 18

#define enc4cha 15
#define enc4chb 2
#define LPWM4 26
#define RPWM4 33

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
float eprev1=0;
float eprev2=0;
float eprev3=0;
float eprev4=0;
int s=0;
float kp1 = 1;
float kd1 =0;   
float ki1 =0;

float kp2 = 1;
float kd2 =0;   
float ki2 =0;

float kp3 = 1;
float kd3 =0;   
float ki3 =0;

float kp4 = 1;
float kd4 =0;   
float ki4 =0;

 
void setup() {
  PS4.begin("1a:2b:3c:00:00:00");
  Serial.begin(115200);
  pinMode(enc1cha, INPUT_PULLUP);
  pinMode(enc1chb, INPUT_PULLUP);
  pinMode(LPWM1, OUTPUT);
  pinMode(RPWM1, OUTPUT);

  pinMode(enc2cha, INPUT_PULLUP);
  pinMode(enc2chb, INPUT_PULLUP);
  pinMode(LPWM2, OUTPUT);
  pinMode(RPWM2, OUTPUT);

  pinMode(enc3cha, INPUT_PULLUP);
  pinMode(enc3chb, INPUT_PULLUP);
  pinMode(LPWM3, OUTPUT);
  pinMode(RPWM3, OUTPUT);

  pinMode(enc4cha, INPUT_PULLUP);
  pinMode(enc4chb, INPUT_PULLUP);
  pinMode(LPWM4, OUTPUT);
  pinMode(RPWM4, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(enc1cha), encoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(enc2cha), encoder2, RISING);
  attachInterrupt(digitalPinToInterrupt(enc3cha), encoder3, RISING);
  attachInterrupt(digitalPinToInterrupt(enc4cha), encoder4, RISING);

}

void loop()
{
  
float setrpm=s;
s=100;
unsigned long currentmillis = millis();
float deltaT = ((float)(currentmillis - previousmillis)) / 1000;
  if (currentmillis - previousmillis >= interval)
  {
    int ticks1 = encoderticks1;
    encoderticks1 = 0;
    float rpm1 = ticks1*0.1;
    float e1 = setrpm - rpm1;
    float dedt1=(e1-eprev1)/deltaT;
    eintegral1 = eintegral1 + e1 * deltaT;
    float u1 =kp1*e1 + kd1*dedt1 + ki1*eintegral1;
    
   
  int ticks2 = encoderticks2;
  encoderticks2 = 0;
  float rpm2 = ticks2*0.1;
  float e2 = setrpm - rpm2;
  float dedt2=(e2-eprev2)/deltaT;
  eintegral2 = eintegral2 + e2 * deltaT;
  float u2 =kp2*e2 + kd2*dedt2 + ki2*eintegral2;
    
     


   int ticks3 = encoderticks3;
   encoderticks3 = 0;
   float rpm3 = ticks3*0.1;
   float e3 = setrpm - rpm3;
   float dedt3=(e3-eprev3)/deltaT;
    eintegral3 = eintegral3 + e3 * deltaT;
    float u3 =kp3*e3 + kd3*dedt3 + ki3*eintegral3;
     

   int ticks4 = encoderticks4;
  encoderticks4 = 0;
  float rpm4 = ticks4*0.1;
  float e4 = setrpm - rpm4;
  float dedt4=(e4-eprev4)/deltaT;
    eintegral4 = eintegral4 + e4 * deltaT;
    float u4 =kp4*e4 + kd4*dedt4 + ki4*eintegral4;
        
       int pwr1 = u1+(int)(setrpm*1);
       int pwr2 = u2+(int)(setrpm*1);
       int pwr3 = u3+(int)(setrpm*1);
       int pwr4 = u4+(int)(setrpm*1);

        pwr1 = u1;
        pwr2 = u2;
        pwr3 = u3;
        pwr4 = u4;

         if(pwr1>255)
       {
        pwr1=255;
       }

       if(pwr2>255)
       {
        pwr2=255;
       }

       if(pwr3>255)
       {
        pwr3=255;
       }
       if(pwr4>255)
       {
        pwr4=255;
       }

if(PS4.Triangle())
     {
     
       if(pwr1>0)
       {
        analogWrite(LPWM1,pwr1);
        analogWrite(RPWM1,0);
       }
       else if(pwr1<0)
       {
        analogWrite(LPWM1,0);
        analogWrite(RPWM1,pwr1);
       }
       if(pwr2>0){
         analogWrite(RPWM2,pwr2);
         analogWrite(LPWM2,0);
       }
       else if(pwr2<0)
      {
        analogWrite(LPWM2,0);
        analogWrite(RPWM2,pwr2);
      }
       if(pwr3>0){
    analogWrite(RPWM3,pwr3);
    analogWrite(LPWM3,0);
    }
    else if(pwr3<0)
    {
      analogWrite(RPWM3,0);
      analogWrite(LPWM3,pwr3);
    }  
       if(pwr4>0){
    analogWrite(LPWM4,pwr4);
    analogWrite(RPWM4,0);
    }
    else if(pwr4<0)
    {
      analogWrite(LPWM4,0);
      analogWrite(RPWM4,pwr4);
    }
 }
   

    if(PS4.Square())
     {
         if(pwr1>0)
       {
        analogWrite(RPWM1,pwr1);
    analogWrite(LPWM1,0);
       }
       else if(pwr1<0)
       {
        analogWrite(RPWM1,0);
      analogWrite(LPWM1,pwr1);
       }
      
   
if(pwr2>0){
    analogWrite(RPWM2,pwr2);
    analogWrite(LPWM2,0);}
    else if(pwr2<0)
    {
      analogWrite(LPWM2,0);
      analogWrite(RPWM2,pwr2);
    }
       
   
if(pwr3>0){
    analogWrite(LPWM3,pwr3);
    analogWrite(RPWM3,0);}
    else if(pwr3<0)
    {
      analogWrite(LPWM3,0);
      analogWrite(RPWM3,pwr3);
    }  
    
   
if(pwr4>0){
    analogWrite(LPWM4,pwr4);
    analogWrite(RPWM4,0);}
    else if(pwr4<0)
    {
      analogWrite(LPWM4,0);
      analogWrite(RPWM4,pwr4);
    
     }
     }

  if(PS4.Cross())
     {
   
 if(pwr1>0)
       {
        analogWrite(RPWM1,pwr1);
    analogWrite(LPWM1,0);
       }
       else if(pwr1<0)
       {
        analogWrite(RPWM1,0);
      analogWrite(LPWM1,pwr1);
       }
      
   
if(pwr2>0){
    analogWrite(LPWM2,pwr2);
    analogWrite(RPWM2,0);}
    else if(pwr2<0)
    {
      analogWrite(RPWM2,0);
      analogWrite(LPWM2,pwr2);
    }
       
   
if(pwr3>0){
    analogWrite(LPWM3,pwr3);
    analogWrite(RPWM3,0);}
    else if(pwr3<0)
    {
      analogWrite(LPWM3,0);
      analogWrite(RPWM3,pwr3);
    }  
    
   
if(pwr4>0){
    analogWrite(RPWM4,pwr4);
    analogWrite(LPWM4,0);}
    else if(pwr4<0)
    {
      analogWrite(RPWM4,0);
      analogWrite(LPWM4,pwr4);
    }
     }

    if(PS4.Circle())
     {
       if(pwr1>0)
       {
        analogWrite(LPWM1,pwr1);
    analogWrite(RPWM1,0);
       }
       else if(pwr1<0)
       {
        analogWrite(LPWM1,0);
      analogWrite(RPWM1,pwr1);
       }
      
   
if(pwr2>0){
    analogWrite(LPWM2,pwr2);
    analogWrite(RPWM2,0);}
    else if(pwr2<0)
    {
      analogWrite(RPWM2,0);
      analogWrite(LPWM2,pwr2);
    }
       
   
if(pwr3>0){
    analogWrite(RPWM3,pwr3);
    analogWrite(LPWM3,0);}
    else if(pwr3<0)
    {
      analogWrite(RPWM3,0);
      analogWrite(LPWM3,pwr3);
    }  

    if(pwr4>0){
    analogWrite(RPWM4,pwr3);
    analogWrite(LPWM4,0);}
    else if(pwr3<0)
    {
      analogWrite(RPWM4,0);
      analogWrite(LPWM4,pwr4);
    } 
}

     
   
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
    eprev1=e1;
    eprev2=e2;
    eprev3=e3;
    eprev4=e4;
    previousmillis=currentmillis;
  }
  

  


  if(PS4.Up())
  {
    analogWrite(LPWM1,0);
    analogWrite(RPWM1,0);
    analogWrite(LPWM2,0);
    analogWrite(RPWM2,0);
    analogWrite(LPWM3,0);
    analogWrite(RPWM3,0);
    analogWrite(LPWM4,0);
    analogWrite(RPWM4,0);
    
  }
  

}



void encoder1() {
  encoderticks1++;
}

void encoder2() {
  encoderticks2++;
}

void encoder3() {
  encoderticks3++;
}

void encoder4() {
  encoderticks4++;
}
