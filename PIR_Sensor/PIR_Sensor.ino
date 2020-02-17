#include <LiquidCrystal.h>    
int ledPin = 13;                // choose the pin for the LED
int inputPin = 7;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int pinSpeaker = 10;           //Set up a speaker on a PWM pin (digital 9, 10, or 11)
 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);                          // initialize the library with the numbers of the interface pins
 
void setup() {  pinMode(ledPin, OUTPUT); // declare LED as output  pinMode(inputPin, INPUT); // declare sensor as input
  pinMode(pinSpeaker, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(2, 0);                                            // Set LCD cursor position (column, row)
  lcd.print("P.I.R Motion");                                      // Print text to LCD
  lcd.setCursor(5, 1);                                            // Set LCD cursor position (column,row)
  lcd.print("Sensor");                                            // Print text to LCD
  delay(4000); // wait 4s                                      // Delay to read text
  lcd.clear(); // clear LCD display                               // Clear the display
  lcd.setCursor(2, 0);                                            // Set LCD cursor position (column, row)
  lcd.print("Developed By");                                     // Print text to LCD
  lcd.setCursor(2, 1);                                            // Set LCD cursor position (column, row)
  lcd.print("Zishan Ahmad");                                         // Print text to LCD                                                                                                                                                                                                                                                                                                                                                                                                                       
delay(5000);                                                      // Delay to read text
lcd.clear();                                                    // Clear LCD   
lcd.setCursor(0, 0);
      lcd.print("Processing Data.");
      delay(3000);
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Waiting For");
      lcd.setCursor(3, 1);
      lcd.print("Motion....");     
}
void loop(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    playTone(300, 300);
    delay(150);
 
   
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      lcd.clear() ;
      lcd.setCursor(0, 0);                                           // Set LCD cursor position (column 0, row 0)
      lcd.print("Motion Detected!");  
     
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
      digitalWrite(ledPin, LOW); // turn LED OFF
      playTone(0, 0);
      delay(300);   
      if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      lcd.clear() ;
      lcd.setCursor(3, 0);
      lcd.print("Waiting For");
      lcd.setCursor(3, 1);
      lcd.print("Motion....");      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
// duration in mSecs, frequency in hertz
void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 100000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}
