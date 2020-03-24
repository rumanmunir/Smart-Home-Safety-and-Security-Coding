
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define _SS_MAX_RX_BUFF 512
#define tempSensor 12

LiquidCrystal lcd (40,41,42,43,44,45); // Configure pins for LCD display
SoftwareSerial SIM900(10,11);  // Configure software serial ports for GSM module. 

//----------------> This function read keypad and send values<---------------------

String readKeypadInput(byte loopVal)
{
 char tempMobile[12];
 
for(int j=0; j<=loopVal-1; j++)
{
  char key = keypad.waitForKey();
if(key != '*' && key!='#' && key!='A'&& key!='B'&& key!='C'&& key!='D')
 {
 Serial.print(key);
 lcd.print(key);
 tempMobile[j]=key;
 tempMobile[j+1]='\0';

 }
if( key == '*') // If user press '*' clear characters on the lcd. If there is a mistake it will be gone automatically
{
clearInput();
j=-1;
  }
 if ( j<=loopVal && key == '#')
 {

if(mobileNumber == "EMPTY" || pinCode == "EMPTY")
  {
    withoutRegisterMsg();
    return "0";
  }
byte val = goBackMsg();
if(val == 1)
{
  return "1";
}
 else if(val ==0 )
{
   return "0"; 

}
  

 
 }
if(j == loopVal-1 && key!='#'&& key!='A'&& key!='B'&& key!='C'&& key!='D')
  {
    return tempMobile;
   
  }

if ( key=='A'|| key=='B'|| key=='C'|| key=='D')
 {
   invalidInput();
   clearInput();
  j=-1;
  }
}
}
void clearInput()
{
  lcd.setCursor(0,1);
  lcd.print(F("                    "));
  lcd.setCursor(0,1);
}
//void inputMessage()
//{
//  lcd.setCursor(0,1);
//  lcd.print(F("First Complete input"));
//  delay(1500);
// }
void invalidInput()
{
  lcd.setCursor(0,1);
  lcd.print(F("Invalid Input!"));
  delay(1000);
}

//  ---------------->This functions ends here<---------------------

byte mainMenu()
{
  String temp;
byte check;  
mainMenuScreen();
 char key;
    while(key != 'A' || key != 'B' || key != 'C' || key != '#')
  {
   key = keypad.waitForKey();
  if(key == 'A')
   {
    changeMsg();
    check = getPin();
    if(check ==0)   // If user selects exit to system then break.
      {
       break;
       }
     else if(check ==3)  // If pin is correct. 
     {
      sureMsg();   // Then ask confirmation to change mobile
      while(key != '*' || key !='#')
      {
        key = keypad.waitForKey();
        if(key =='*')   // If user select No then return to the main system
        {
          mainMenuScreen();
          break;
        }
       if(key =='#')  // If user select Yes then show the mobile menu
        {
        temp = saveMobileNumber();
        if(temp == "0")
        {
          return;
        }
        else
        {
         mobileNumber = temp;
        savingDataMsg();
        writeEEPROM(1,0,0,0,0);
        mainMenuScreen();
        break;
        }
        }
       }
      }
 }
    else if (key == 'B')
     {
      changeMsg();         // If user need to continue is should enter pin code
      check = getPin();    // Verify pin
       if(check ==0)        // If user selects exit to system then display
       {
        break;
       }
       else if(check ==3)   // If pin is correct 
        {
      sureMsg2();            // User will be asked to sure about changing pin
      while(key != '*' || key !='#')
       {
        key = keypad.waitForKey();
        if(key =='*')
        {
        mainMenuScreen();
          break;             // If user selects no then return to main system
        }
       if(key =='#')          //If user selects yes then 
        {
        temp = savePin();  // Show the user the pin screen
          if(temp == "0")
          {
            return ;
          }
          else 
          {
            pinCode = temp;
       savingDataMsg();
        writeEEPROM(0,1,0,0,0);
        mainMenuScreen();
        break;
          }
        }
       }
      }
    }
else if(key =='C')
  {
     changeMsg();
      check = getPin();    // Verify pin
       if(check ==0)        // If user selects exit to system then exit
       {
        break;
       }
       else if(check ==3)  // If pin is correect 
       {
         check = neighboursMenu();
          if(check == 0)
          {
            mainMenuScreen();
            continue;
          }
       }
 
  }
  else if(key =='#')
  {
  break;
  }
 }  
}


void changeMsg()
{
lcd.clear();
lcd.print(F("In order to change"));
lcd.setCursor(0,1);
lcd.print(F("anything.You need to"));
lcd.setCursor(0,2);
lcd.print(F("Enter Pin Code"));
lcd.setCursor(16,3);
respondOk();
}
void sureMsg()
{
lcd.clear();
lcd.print(F("Are you sure about"));
lcd.setCursor(0,1);
lcd.print(F("changing mobile"));
lcd.setCursor(0,2);
lcd.print(F("Number?"));
lcd.setCursor(0,3);
lcd.print(F("*-NO"));
lcd.setCursor(15,3);
lcd.print(F("#-YES"));
}
void sureMsg2()
{
lcd.clear();
lcd.print(F("Are you sure about"));
lcd.setCursor(0,1);
lcd.print(F("Changing Pin Code?"));
lcd.setCursor(0,3);
lcd.print(F("*-NO"));
lcd.setCursor(15,3);
lcd.print(F("#-YES"));
}


//----------------> This  function write data to EEPROM<---------------------
void writeEEPROM(byte val1,byte val2, byte val3,byte val4,byte val5)
{
  Serial.println(F("Writing data to EEPROM"));
if(val1 == 1) // Write Data for mobileNumber global variable
{
for(int i=0; i<=12; i++)
 {
   EEPROM.write(i,mobileNumber[i]);
   delay(200);
 }
}

if(val2 == 1)       // Write Data for pinCode global variable
{
for(int i=13,j=0; i<=16; i++,j++)
 {
   EEPROM.write(i,pinCode[j]);
   delay(200);
 }
}

if(val3 == 1)   // Write Data for Neighbour1 global variable
{
for(int i=17,j=0; i<=29; i++,j++)
 {
   EEPROM.write(i,neigbhour1[j]);
   delay(200);
 }
}
if(val4 == 1)  // Write Data for Neighbour2 global variable
{
for(int i=30,j=0; i<=42; i++,j++)
 {
   EEPROM.write(i,neigbhour2[j]);
   delay(200);
 }
}
if(val5 == 1)  // Write Data for Neighbour3 global variable
{
for(int i=43,j=0; i<=55; i++,j++)
 {
   EEPROM.write(i,neigbhour3[j]);
   delay(200);
 }
}

}

//----------------> This retrieve data from EEPROM<---------------------
void readEEPROM()
{
Serial.println(F("Reading data from EEPROM"));
String readMobile="";
String readPin="";
String readNeighour1="";
String readNeighour2="";
String readNeighour3="";
String readAddressLen="";
String readAddress="";
for(int i=0;i<=12;i++)
 {
 char a=EEPROM.read(i); 
 readMobile = readMobile+a;
 }
for(int i=13;i<=16;i++)
 {
 char a=EEPROM.read(i); 
 readPin = readPin+a;
 }
 for(int i=17;i<=29;i++)
 {
 char a=EEPROM.read(i); 
 readNeighour1 = readNeighour1+a;
 }
 for(int i=30;i<=42;i++)
 {
 char a=EEPROM.read(i); 
 readNeighour2 = readNeighour2+a;
 }
 for(int i=43;i<=55;i++)
 {
 char a=EEPROM.read(i); 
 readNeighour3 = readNeighour3+a;
 }
 for(int i=56;i<=57;i++)
 {
 char a=EEPROM.read(i); 
 readAddressLen = readAddressLen+a;
 
 }
 addressLen = readAddressLen.toInt();
 
 for(int i=58; i<=58+addressLen; i++)
 {
 char a=EEPROM.read(i); 
 readAddress = readAddress+a;
 }
 

Serial.println(F("Mobile"));
Serial.println(readMobile);
Serial.println(F("Pin"));
Serial.println(readPin);
Serial.println(F("Neighbour1"));
Serial.println(readNeighour1);
Serial.println(F("Neighbour2"));
Serial.println(readNeighour2);
Serial.println(F("Neighbour3"));
Serial.println(readNeighour3);
Serial.println(F("Address Length"));
Serial.println(readAddressLen);
Serial.println(F("Address"));
Serial.println(readAddress);


if(!readNeighour1.startsWith("+923",0))
{
  neigbhour1 = "EMPTY";
}
else 
{
  neigbhour1 = readNeighour1;
}
if(!readNeighour2.startsWith("+923",0))
{
  neigbhour2 = "EMPTY"; 
}
else
{
  neigbhour2 = readNeighour2;
}
if(!readNeighour3.startsWith("+923",0))
{
  neigbhour3 = "EMPTY";
}
else
{
 neigbhour3 = readNeighour3;
  
}
if(!readMobile.startsWith("+923",0))
{
  mobileNumber = "EMPTY";
  pinCode = "EMPTY";
}
else
{
  mobileNumber = readMobile;
  pinCode =readPin;
 }
if(addressLen <= 0)
{
  address = "EMPTY";
}
else
{
   address = readAddress;
}
  
}
void clearEEPROM()
{
Serial.println(F("Deleting Everything from EEPROM"));
 for(int i=0; i<=125; i++)
 {
 EEPROM.write(i,0);
 delay(200);
 }
}

void clearByEEPROM(byte val1,byte val2,byte val3)
{
Serial.println("Deleting from EEPROM");
 if(val1 ==1) // Deleteing Neighbour 1 in memory
 {
 for(int i=17; i<=29; i++)
 {
 EEPROM.write(i,0);
 delay(200);
 }
}
 if(val2 ==1)  // Deleteing Neighbour 2
 {
 for(int i=30; i<=42; i++)
 {
 EEPROM.write(i,0);
 delay(200);
 }
}
 if(val3 ==1)   // Deleteing Neighbour 3
 {
 for(int i=43; i<=55; i++)
 {
 EEPROM.write(i,0);
 delay(200);
 }
}
}
