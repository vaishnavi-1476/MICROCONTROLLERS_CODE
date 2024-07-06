volatile long temp, counter = 0; // Counter variable that increases or decreases based on encoder rotation
#define ena1 19
#define enb1 32

#define ena2 18
#define enb2 30

#define ena3 3
#define enb3 28

#define ena4 2
#define enb4 34

int encoderticks1=0;
int encoderticks2=0;
int encoderticks3=0;
int encoderticks4=0;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  
  pinMode(ena1, INPUT_PULLUP); // Set pin 2 as input with internal pull-up resistor
  pinMode(enb1, INPUT_PULLUP); // Set pin 3 as input with internal pull-up resistor
    pinMode(ena2, INPUT_PULLUP); // Set pin 2 as input with internal pull-up resistor
  pinMode(enb2, INPUT_PULLUP);
    pinMode(ena3, INPUT_PULLUP); // Set pin 2 as input with internal pull-up resistor
  pinMode(enb3, INPUT_PULLUP);
    pinMode(ena4, INPUT_PULLUP); // Set pin 2 as input with internal pull-up resistor
  pinMode(enb4, INPUT_PULLUP);
  // Attach interrupts to pin 2 (ena) and pin 3 (enb)
  attachInterrupt(digitalPinToInterrupt(ena1), encoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(ena2), encoder2, RISING);
    attachInterrupt(digitalPinToInterrupt(ena3), encoder3, RISING);
      attachInterrupt(digitalPinToInterrupt(ena4), encoder4, RISING);
}

void loop() {
  // Send the value of counter if it has changed
//  if (counter != temp) {
//    Serial.println(counter);
//    temp = counter;
//  }
 Serial.print("motor 1: ");
  Serial.print(encoderticks1);
   Serial.print("motor 2: ");
    Serial.print(encoderticks2);
     Serial.print("motor 3: ");
      Serial.print(encoderticks3);
       Serial.print("motor 4: ");
        Serial.print(encoderticks4);
         Serial.println("");
}

// Interrupt service routine for pin 2 (ena)
void encoder1() {
  // Check the state of pin 3 (enb) to determine the direction of rotation
  if (digitalRead(32) == LOW) {
    
encoderticks1++; // Increment counter if pin 3 is LOW
  } else {
   
encoderticks1--; // Decrement counter if pin 3 is HIGH
  }
}

// Interrupt service routine for pin 3 (enb)
void encoder2() {
  // Check the state of pin 2 (ena) to determine the direction of rotation
  if (digitalRead(30) == LOW) {
    
encoderticks2++;; // Decrement counter if pin 2 is LOW
  } else {
    
encoderticks2--; // Increment counter if pin 2 is HIGH
  }
}
void encoder3() {
  // Check the state of pin 3 (enb) to determine the direction of rotation
  if (digitalRead(28) == LOW) {
   
encoderticks3++; // Increment counter if pin 3 is LOW
  } else {
   
encoderticks3--; // Decrement counter if pin 3 is HIGH
  }
}
void encoder4() {
//   Check the state of pin 3 (enb) to determine the direction of rotation
  if (digitalRead(34) == LOW) {
   
encoderticks4++; // Increment counter if pin 3 is LOW
  } else {
    
encoderticks4--; // Decrement counter if pin 3 is HIGH
  }
}
