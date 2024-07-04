#define m11 PB6
#define m12 PB7
int i;

void setup() {
  pinMode(m11,OUTPUT);
  pinMode(m12,OUTPUT);
  Serial.begin(9600);

}

void loop() {
 for(int i=0;i<1000;i++){
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  Serial.println(i);
 }
  for(int i=1000;i>0;i--){
     digitalWrite(m11,LOW);
  digitalWrite(m12,HIGH);
  Serial.println(i);
 
 }
  
}
