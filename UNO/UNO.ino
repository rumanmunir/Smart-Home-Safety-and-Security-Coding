//lcd display 
#include <LiquidCrystal.h> 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int Contrast=100;
//lcd


//touch

int touchpin = A1;
int val = 0;
int output1 = 8;

//touch

//rain 

int output2 = 6;
int rainsense= A0;
int countval= 0;

//rain 


//ultrasonic
const int trigPin = 9;
const int echoPin = 10;
const int output3 = 7;

// defines variables
long duration;
int distance;
int safetyDistance;

//ultrasonic

//LDR
const int output4 = 13;

const int ldrPin = A2;

//LDR

void setup(){
  Serial.begin(9600);

  //ldr
  pinMode(output4, OUTPUT);

  pinMode(ldrPin, INPUT);
  //ldr
  //ultrasonic

pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(output3, OUTPUT);
  
  //ultrasonic
   pinMode(rainsense, INPUT);
   pinMode(output2, OUTPUT);
  analogWrite(6,Contrast);
  lcd.begin(16,2);
  lcd.setCursor(0, 0);  // ROws * Columns
  lcd.print("SMART HOME ");
  lcd.setCursor(0, 1);
  lcd.print("AUTOMATION"); 
  Serial.begin(9600);
  pinMode(touchpin, INPUT);
  pinMode(output1, OUTPUT);
  
  }

  void loop(){
    //Rain sensor
  int sensorvalue=analogRead(rainsense);
  Serial.println(sensorvalue);
  
  if(sensorvalue<=500){
    Serial.print("Heavy rain");
    lcd.clear();
    lcd.print("WEATHER STATUS:");
    lcd.setCursor(0,1);
    lcd.print("RAINING");
      digitalWrite(output2, HIGH);
    
    
  }
  else
  {
    digitalWrite(output2, LOW);
  }
    
     //rain sensor end

     //ldr

    int ldrStatus = analogRead(ldrPin);

if (ldrStatus <=5) { 

    digitalWrite(output4, HIGH);
    Serial.println();
    lcd.clear();
    lcd.print("STREET LIGHTS:");
    lcd.setCursor(0,1);
    lcd.print("ON / OFF");

Serial.println("LDR is DARK, LED is ON");
Serial.println(ldrStatus);
}

else {

digitalWrite(output4, LOW);

Serial.println("LED OFF");
Serial.println(ldrStatus);

}
     //ldr End

    // Ultra Sonic
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

safetyDistance = distance;
if (safetyDistance <= 5 && safetyDistance >0){
  digitalWrite(output3, HIGH);
  Serial.println("safetyDistance:");
  Serial.println(safetyDistance);
  lcd.clear();
    lcd.print("BE CAREFUL :");
    lcd.setCursor(0,1);
    lcd.print("OBJECT DETECTED");
  
}
else{
  digitalWrite(output3, LOW);
  Serial.println(safetyDistance);
}

    
    // Ultra Sonic end
     
    //touch sensor
    digitalWrite(output1, LOW);
  val = digitalRead(touchpin);
  if(val == 1){
    Serial.print("Touched");
    lcd.clear();
    lcd.print("DOOR STATUS:");
    lcd.setCursor(0,1);
    lcd.print("UNLOCK");
    digitalWrite(output1, HIGH);
    
  }
  delay(2000);
  //touch sensor end
  }
