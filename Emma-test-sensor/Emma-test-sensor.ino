#include <Adafruit_MotorShield.h>

// pin setup
int LSensorPin = A0;
int RSensorPin = A1;

// initialize variables
int LSensor, RSensor;

void setup() {
  // start serial port and AFMS
  Serial.begin(9600);

  // Initiate IR sensors as inputs
  pinMode(LSensorPin,INPUT);
  pinMode(RSensorPin,INPUT);

  // Read Sensor Values
  LSensor = analogRead(LSensorPin);
  RSensor = analogRead(RSensorPin);
}

void loop() {
  
  // Take both sensor inputs
  LSensor = analogRead(LSensorPin);
  RSensor = analogRead(RSensorPin);

  //Serial.print("Left Sensor Value");
  //Serial.println(LSensor");

  //Serial.print("Right Sensor Value");
  Serial.println(RSensor);


}

