  #define BLYNK_PRINT Serial  // use to Show output on blynk app
  #include <ESP8266WiFi.h>    // nodemcu wifi library
  #include <DHT_U.h>
  #include <BlynkSimpleEsp8266.h> // blynk library for nodemcu esp8266
  #include <DHT.h> //DHT Sensor Library
  


  char auth[] = "9a302791ef9647589756a1bcc9f59ab2"; // Authantication Token For Blynk Server Connection...!
  char ssid[] = "SMART HOME AUTOMATION"; // wifi name
  char pass[] = "DEVELOPER TEAM";  //  wifi password 

  // 2 start

  #define DHTPIN 0       // D3 I/O pin for DHT11 U may Use Another Pin...!
 
  // Uncomment whatever type you're using!
  #define DHTTYPE DHT11     // DHT 11
  //#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
  //#define DHTTYPE DHT21   // DHT 21, AM2301
 
  DHT dht(DHTPIN, DHTTYPE);  // DHT funtion with pyrameter of pin no and type
   BlynkTimer timer;            //timer to chek temperature means how many time gap to check change in temperature
 
  // This function sends Arduino's up time every second to Virtual Pin (5).
  // In the app, Widget's reading frequency should be set to PUSH. This means
  // that you define how often to send data to Blynk App.
  void sendSensor() // funtion u may use any other name for your function
  {
  float h = dht.readHumidity(); // input value of humidity
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
 
  if (isnan(h) || isnan(t)) // Condition
  { 
    Serial.println("Failed to read from DHT sensor!");   // when it is not connected or some error to read value of temperature
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);   // v5 for humidity
  Blynk.virtualWrite(V6, t);   // v6 for temperature
}

// 2 end

// Gas Leakage
int gasA0 = A0;   // AO pin Analog Input
int sensorThres = 150;  //Max Value Of Gas


// Common Output 
const int output1 = 16; //output pin D0
const int output2 = 2 ;//output pin D4


//Flame sensor
const int flamepin = 4; // D2 flame Input Pin
int Flame = LOW; // sensor state Intially


void setup() // Setup For Whole Project
{
  Serial.begin(9600); // Work as Console
  
  Blynk.begin(auth, ssid, pass); // connection with blynk server
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
 
  dht.begin(); // start dht
 timer.setInterval(1000L, sendSensor);  // chek value every scnd
  
  
  // pinmode for gas sensor
  pinMode(gasA0, INPUT); // input mode for gas sensor
  pinMode(output1, OUTPUT); // Output1 pin For Alarm...!

  
  // pinmode for flame sensor / fire sensor 
  pinMode(output2, OUTPUT); // Output1 pin For Alarm...!
  pinMode(flamepin, INPUT); //work as Input to reaed data from flame sensor

 pinMode(D1,INPUT_PULLUP); // door security pin mode as input
   timer.setInterval(10000L,notifyOnButtonPress); // time gap to chek status
  
}
  //3 start

int flag=0; // for  door notification
 
 void notifyOnButtonPress(){ // door security function
 int isButtonPressed = digitalRead(D1); // door stAtus 
  if (isButtonPressed==1 && flag==0){ //when condition true
    Serial.println("This is Message From Smart Home Automation Developer Team That Someone Has Open Your Door"); // output on serial monitor
    Blynk.notify("Alert \n Someone Has Open Your Door"); // // output on Mobile Screen Notification
    flag=1; // flag status return 1 condition after updAte
  }
  else if (isButtonPressed==0){
    flag=0; // return 0 into its initial value
  }
 }

// 3
  
  
  void loop (){ // repaeting function in the form of loop

    
  //Gas Sensor code 
  int analogSensor = analogRead(gasA0);   // set input value in max level of gas
  Serial.print("Pin A0: "); // output in serial Monitor of arduino software
  Serial.println(analogSensor);// show input value on serial monitor of arduino software
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)   //Gas Sensor condition
  {
    digitalWrite(output1,LOW); // When Condition Is True
    Blynk.notify("DANGER...!\n Gas Leakage Detected"); // out put on mobile notification
  }
  else
  {
    digitalWrite(output1,HIGH);  // When Condition Is False
  }
  delay(100); // time gap for gas sensor reading
  

 
  
  //flame sensor
     Flame = digitalRead(flamepin);
  if(Flame == LOW){
    digitalWrite(output2,LOW);  // when condition is true
    Blynk.notify("DANGER...!\n Fire In The House");  
  }
  else{
    digitalWrite(output2, HIGH);  // when condition is false
  }


   Blynk.run(); // Run blynk server 
   timer.run(); // run timer 
  
  }
