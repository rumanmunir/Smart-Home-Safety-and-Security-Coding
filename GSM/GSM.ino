#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <EEPROM.h>
#include <OneWire.h>
void setup()
{
//  clearEEPROM();       // This line of code is used to delete stored numbers and pin code from the internal memory
  SIM900.begin(19200);
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  SIM900.print("AT+GSMBUSY=1\r");
  Serial.begin(9600);
  sensors.begin();
  pinMode(motionSensor, INPUT);
  pinMode(Alarm,OUTPUT);
  pinMode(flameSensor,INPUT);
  pinMode(smokeSensor,INPUT);
  randomSeed(analogRead(0)); // Initilizing Random Seed Values and a holder
  //delay(20000); // Give time to your GSM shield log on to network

 readEEPROM();
welcomeScreen();
 
  if(mobileNumber == "EMPTY") // If Mobile Number is empty which means we need to register first otherwise we will move towards main fucntion
 { 
  registerScreen();
  mobileNumber = saveMobileNumber(); // Store the mobile Number in global variable
  pinCode = savePin();  // Store the pin in global variable
  savingDataMsg();
  writeEEPROM(1,1,0,0,0);
  } 
lcd.clear(); 
}

void loop()
{
if(SIM900.available())
  {
    textMessage = SIM900.readString();
  
   }
   if(textMessage.indexOf("+CMT") >=0 )
   {
    Serial.println(F("New Message is received +CMT"));
    Serial.println(textMessage); 
    check_SMS();
    lcd.clear();
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
void sendSMS(String mobile, byte SmsType,unsigned int value , String temp) {
  
  sendingSmsMsg();
  
  SIM900.print("AT+CMGF=1\r"); // AT command to set SIM900 to SMS mode 
  delay(100);

  SIM900.println("AT + CMGS = \"" + mobile +"\"");  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
   delay(100);                                     // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS

  if(SmsType == 0){
   SIM900.println(F("Your GSM Security Code : "));  // SET MESSAGE CONTENT
   SIM900.println(value);
   delay(100);
  }
   else if(SmsType == 1)
   {
     
    SIM900.print(F("Your number ")); 
    SIM900.print(mobile); 
     SIM900.print(F(" is successfully registered with GSM Security Module.")); 
     delay(100);
   }

   else if(SmsType == 2)
   {
    SIM900.print(F("Your Password for GSM Security System ")); 
    SIM900.print(temp); 
    delay(100);
  }
   
  SIM900.println((char)26);  // End AT command with a ^Z, ASCII code 26
  delay(100);
  SIM900.println();
  delay(3000);    // Give module time to send SMSa

return ;

}
    
