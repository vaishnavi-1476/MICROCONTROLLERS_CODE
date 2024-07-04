/* LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define Switch  A4

char RFID_input[12]={0};
int count = 0;
int Total_Cost = 0;
int Total_items = 0;
int Item1_cnt = 0;
int Item2_cnt = 0;

void setup() 
{
  // set up the LCD's number of columns and rows:
  pinMode(Switch, INPUT_PULLUP);
  Serial.begin(9600);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print(" AUTOMATIC BILL");
  lcd.setCursor(0, 1);
  lcd.print(" SHOPPING CART ");
  delay(2000);

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("WELCOME TO");
  lcd.setCursor(2, 1);
  lcd.print("SUPER MARKET");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cart is Empty");
  lcd.setCursor(3, 1);
  lcd.print("Add items");
}

void loop() 
{
  if(Serial.available() > 0)
  {
     count = 0; // Reset the counter to zero
      
      while(Serial.available() && count < 12) 
      {
        RFID_input[count] = Serial.read(); // Read 1 Byte of data and store it in the input[] variable
        count++; // increment counter 
        delay(5); 
      }
      for(int i=0; i<12; i++)
      {
        Serial.print(RFID_input[i]);
      }
   
      //Card Data,
      //0002264277 034 , 36053: 2700228CD55C  Sugar 1Kg: Rs.55
      //0002264421 034 , 36197: 2700228D65ED  Rice 1Kg: Rs.84
      
      //sugar added
      if((strncmp(RFID_input, "2700228CD55C", 12) == 0) && (digitalRead(Switch) == 1))
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sugar Added");
        lcd.setCursor(0, 1);
        lcd.print("Price: Rs.55");
        Total_Cost = Total_Cost + 55;
        delay(1000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Total Price:");
        lcd.setCursor(0, 1);
        lcd.print("Rs.");
        lcd.print(Total_Cost);
        Total_items = Total_items + 1;
        Item1_cnt = Item1_cnt + 1;
      }

      //Sugar removed 
      else if((strncmp(RFID_input, "2700228CD55C", 12) == 0) && (digitalRead(Switch) == 0))
      {
        if(Item1_cnt > 0)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Sugar Removed");
          Total_Cost = Total_Cost - 55;
          delay(1000);

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Total Price:");
          lcd.setCursor(0, 1);
          lcd.print("Rs.");
          lcd.print(Total_Cost);
          Total_items = Total_items - 1;
          Item1_cnt = Item1_cnt - 1;
        }
      }

      //Rice added
      if((strncmp(RFID_input, "2700228D65ED", 12) == 0) && (digitalRead(Switch) == 1))
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Rice Added");
        lcd.setCursor(0, 1);
        lcd.print("Price: Rs.84");
        Total_Cost = Total_Cost + 84;
        delay(1000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Total Price:");
        lcd.setCursor(0, 1);
        lcd.print("Rs.");
        lcd.print(Total_Cost);
        Total_items = Total_items + 1;
        Item2_cnt = Item2_cnt + 1;
      }

      //Rice Removed
      else if((strncmp(RFID_input, "2700228D65ED", 12) == 0) && (digitalRead(Switch) == 0))
      {
        if(Item2_cnt > 0)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Rice Removed");
          lcd.setCursor(0, 1);
          lcd.print("Price: Rs.84");
          Total_Cost = Total_Cost - 84;
          delay(1000);

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Total Price:");
          lcd.setCursor(0, 1);
          lcd.print("Rs.");
          lcd.print(Total_Cost);
          Total_items = Total_items - 1;
          Item2_cnt = Item2_cnt - 1;
        }
      }
    
    if(Total_items == 0)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Cart is Empty");
      lcd.setCursor(3, 1);
      lcd.print("Add items");
    }
  }
    
}
