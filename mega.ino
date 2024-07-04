int m11=7;//rpwm
int m12=6;//lpwn
int i = 0;

void setup() {
  pinMode(m11,OUTPUT);
  pinMode(m12,OUTPUT);
  Serial.begin(9600);
  
}
void loop()
{
  //forward
  for(int i=0;i<=2000;i++)
  {
  digitalWrite(m11,LOW);
 digitalWrite(m12,HIGH);
 Serial.println(i);
  }
  for(int i=2000;i>=0;i--)
  {
    digitalWrite(m11,HIGH);
 digitalWrite(m12,LOW);
 Serial.println(i);
  }
  
}
