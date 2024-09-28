#include<SoftwareSerial.h>
#include "LiquidCrystal_I2C.h"
SoftwareSerial B(0,1);

LiquidCrystal_I2C lcd(0x3F, 16, 2);
const int sampleWindow = 50;                              // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
const int noPin = 6;
int X=50;
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distanceCm, distanceInch;
 

#define SENSOR_PIN A0

 

void setup() {
  

  Serial.begin(9600); 
  B.begin(9600);
  pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);

  pinMode (SENSOR_PIN, INPUT); // Set the signal pin as input  
  pinMode(noPin, INPUT); // Digital Pin 6. Both input mode.
   pinMode(7, OUTPUT); // Connect LED Pin D6
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  digitalWrite(noPin, LOW);
  
  lcd.begin(16,2);
   lcd.backlight();
    lcd.clear();
  
 

}

void loop() {
   
  digitalWrite(7, LOW);

  digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distanceCm= duration*0.034/2;
distanceInch = duration*0.0133/2;

delay (100);


   unsigned long startMillis= millis();                   // Start of sample window
   float peakToPeak = 0;                                  // peak-to-peak level
 
   unsigned int signalMax = 0;                            //minimum value
   unsigned int signalMin = 1024;                         //maximum value
 
                                                          // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(SENSOR_PIN);                    //get reading from microphone
      if (sample < 1024)                                  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;                           // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;                           // save just the min levels
         }
      }
   }
 
   peakToPeak = signalMax - signalMin;                    // max - min = peak-peak amplitude
   int db = map(peakToPeak,20,900,49.5,90);             //calibrate for deciBels


  if (db > 55)
  {
     lcd.setCursor(0, 0);
  lcd.print("ARE YOU OKAY?");
  digitalWrite(7, HIGH);
  delay(10000);

  if (digitalRead(noPin) == HIGH)
  {
    digitalWrite(7, LOW);
  }
  else
  {
 Serial.println("ABC HAS MET WITH AN ACCIDENT ON STREET XYZ.");
 B.print(";");
 digitalWrite(7, HIGH);
 delay(60000);
 lcd.clear();
 
}
  
      }

       if (distanceCm > 15)
  {
     lcd.setCursor(0, 0);
  lcd.print("ARE YOU OKAY?");
  digitalWrite(7, HIGH);
  delay(10000);

  if (digitalRead(noPin) == HIGH)
  {
    digitalWrite(7, LOW);
  }
  else
  {
 Serial.println("ABC HAS MET WITH AN ACCIDENT ON STREET XYZ.");
 B.print(";");
 digitalWrite(7, HIGH);
 delay(60000);
 lcd.clear();
 
}
  
      }
  
  

}
