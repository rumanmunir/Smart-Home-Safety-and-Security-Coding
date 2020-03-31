
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd (40,41,42,43,44,45); // Configure pins for LCD display
const int buzzerPin = 5;
const int ledPin = 6;
const int motionPin = 7;
const int buttonPin = 12;

// Setting Buzzer mode to False
boolean buzzer_mode = false;

// For LED
int ledState = LOW;
long previousMillis = 0; 
long interval = 100;  // Interval at which LED blinks

void setup()
{
  //The Following are our output
  pinMode(ledPin,OUTPUT);
  pinMode(buzzerPin,OUTPUT);

  //Button is our Input
  pinMode(buttonPin, INPUT);
  
  // Wait before starting the alarm
  delay(5000);
}

void loop()
{
  // To chech whether the motion is detected or not
  if (digitalRead(motionPin)) {
    buzzer_mode = true; 
  }

  // If alarm mode is on,blink our LED
  if (buzzer_mode){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;   
      if (ledState == LOW)
        ledState = HIGH;
      else
        ledState = LOW;
    // Switch the LED
    digitalWrite(ledPin, ledState);
    }
    tone(buzzerPin,1000);
  }

  // If alarm is off
  if (buzzer_mode == false) {
  
    // No tone & LED off
    noTone(buzzerPin);  
    digitalWrite(ledPin, LOW);
  }

  // If our button is pressed Switch off ringing and Setup
  int button_state = digitalRead(buttonPin);
  if (button_state) {buzzer_mode = false;}
}

void readMotion()
{
   lcd.setCursor(0,3);
lcd.print(F("Motion Sensor:"));
lcd.print(motionSen);
   if(motionSen == "ON")
   {
 
  unsigned long currentMillis = millis();
    if(currentMillis - previousMillis5 >= interval3) // Wait for 10 sec
    {
    
   int val = digitalRead(motionSensor);   // read sensor value
  if (val == HIGH)  // check if the sensor is HIGH 
  {           
    sendSMS3(mobileNumber,12);   // turn LED ON
     if (state == LOW) 
    {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else 
  {
      if (state == HIGH)
      {
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
      }
  }
     previousMillis5 =  currentMillis;
      Serial.print("10 Sec passed");
    }
}

}
