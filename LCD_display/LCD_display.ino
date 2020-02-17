#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Capstone1");
  lcd.setCursor(0,1);
  lcd.print("SMART HOME");
  lcd.setCursor(0,2);
  lcd.print("Security & Safet ");
   lcd.setCursor(0,3);
  lcd.print("y System ");
}


void loop()
{
   void welcomeScreen()
{
lcd.begin(20,4);
  lcd.print(F("Welcome to GSM"));
  lcd.setCursor(5,1);
  delay(1000);
  lcd.print(F("Security System"));
  delay(2000);
  }

void registerScreen()
{
lcd.clear();
lcd.print(F("Register Yourself!!"));
lcd.setCursor(0,1);
lcd.print(F("Please Enter Working"));
lcd.setCursor(0,2);
lcd.print(F("Cell Phone Number."));
respondOk();   
}

void numberScreen(){
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Enter Mobile NO:");
  // Serial.print("Mobile:");
   lcd.setCursor(0,2);
  lcd.print("*-Clear Screen");
  lcd.setCursor(0,3);
  lcd.print("#-Continue");
  lcd.setCursor(0,1);
 }

void verificationCodeScreen()
{
lcd.clear();
lcd.print(F("A Verification Code"));
lcd.setCursor(0,1);
lcd.print(F("Has been sent to the"));
lcd.setCursor(0,2);
lcd.print(F("given phone Number."));
respondOk();   
lcd.clear();
lcd.print(F("Please Input Correct"));
lcd.setCursor(0,1);
lcd.print(F("Verification code to"));
lcd.setCursor(0,2);
lcd.print(F("Save Given Phone NUM"));
respondOk();
}
void mainMenuScreen()
{
lcd.clear();
lcd.print(F("A-Change Mobile"));
lcd.setCursor(0,1);
lcd.print(F("B-Change Pin"));
lcd.setCursor(0,2);
lcd.print(F("C-Neighbours"));
lcd.setCursor(14,3);
lcd.print(F("#-Back"));
 }

void deleteSlotEmpty()
{
lcd.clear();
lcd.print(F("This slot is already"));
lcd.setCursor(0,1);
lcd.print(F("Empty.Please Select"));
lcd.setCursor(0,2);
lcd.print(F("Another Slot"));
respondOk();
}

void slotdeleteMsg()
{
lcd.clear();
lcd.print(F("Are you sure?"));
lcd.setCursor(0,1);
lcd.print(F("You want to delete"));
lcd.setCursor(0,2);
lcd.print(F("Slot"));
}
void slotDeleted()
{
lcd.clear();
lcd.print(F("Selected Slot is"));
lcd.setCursor(0,1);
lcd.print(F("successfully deleted"));
respondOk();
}
}
