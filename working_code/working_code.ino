#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

int sensorPinLeft = A1;   // select the input pin for the IR sensor on the left
int sensorPinRight = A0;  // select the input pin for the IR sensor on the right

int sensorValueLeft = 0;  // variable to store the value coming from the sensor
int sensorValueRight = 0;  // variable to store the value coming from the sensor

void setup() {
  pinMode(sensorPinLeft, INPUT);
  pinMode(sensorPinRight, INPUT);

  AFMS.begin();
  leftMotor->run(FORWARD);
  leftMotor->setSpeed(0);
  rightMotor->run(FORWARD);
  rightMotor->setSpeed(0);
  
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorValueLeft = analogRead(sensorPinLeft);
  sensorValueRight = analogRead(sensorPinRight);
  Serial.println(sensorValueLeft);
  Serial.println(sensorValueRight);
  // On: 900 sth
  // Off: 700 sth

  if (sensorValueLeft >= 850) {
    
      Serial.println("Turn right wheel, left wheel stationary");
      leftMotor->setSpeed(10);
      rightMotor->setSpeed(50);
  }
  else if (sensorValueRight >= 850) {
      leftMotor->setSpeed(50);
      rightMotor->setSpeed(10);
  }
  else if (sensorValueLeft >= 850 and sensorValueRight >= 850) {

    Serial.println("Sharp turnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn1");
    leftMotor->setSpeed(250);
    rightMotor->setSpeed(0);
    delay(100);
  }
}