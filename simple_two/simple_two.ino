#include <Adafruit_MotorShield.h>
// initiate motor shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// define ports used for motors
Adafruit_DCMotor *motorR = AFMS.getMotor(2);
Adafruit_DCMotor *motorL = AFMS.getMotor(4);

// pin setup
int L_sensorPin = A0;
int R_sensorPin = A1;

// initialize variables
int L_sensor, R_sensor;
int diff;
int ini_diff;
int speed=20;
String input;
//double threshold_R = 930;
//double threshold_L = 970;



void setup() {
  // start serial port and AFMS
  Serial.begin(9600);
  AFMS.begin();

  // Initiate IR sensors as inputs
  pinMode(L_sensorPin,INPUT);
  pinMode(R_sensorPin,INPUT);

  // Set initial motor speeds to 0
  motorR->setSpeed(0);
  motorL->setSpeed(0);

  // Read Sensor Values
  L_sensor = analogRead(L_sensorPin);
  R_sensor = analogRead(R_sensorPin);

  ini_diff = 10 * (L_sensor - R_sensor);
  while (Serial.available() == 0){}

}

void loop() {
  
  /*if (Serial.available() > 0) {
    // Read until the end of a line
    input = Serial.readStringUntil('\n');

    // Left motor speed
    if (input == 'F') {// F: Fast Mode
      // Both motors are 30
      speed = 30;
      motorR->setSpeed(speed);  
      motorL->setSpeed(speed); 
    }
    // Right motor speed
    if (input == 'S') {// S: Slow Mode
      // Both motors are 20
      speed = 20;
      motorR->setSpeed(speed);  
      motorL->setSpeed(speed); 
    }
 }*/


  // Take both sensor inputs
  L_sensor = analogRead(L_sensorPin);
  R_sensor = analogRead(R_sensorPin);
  //int diff = 10 * (L_sensor - R_sensor);
  speed = 20;

  //Serial.println("R_sensor");
  Serial.println(L_sensor);
  //Serial.println("L_sensor");
  //Serial.println(L_sensor);

  if (diff - ini_diff >= -15 && diff - ini_diff <= 15)
  {
    motorR->setSpeed(speed);  
    motorL->setSpeed(speed); 
   //motorR->run(FORWARD);
   //motorL->run(FORWARD);
   Serial.println("1");
  }
  
  //if (L_sensor < threshold_L && R_sensor > threshold_R)
  if (diff - ini_diff < -15)
  {
  motorR->setSpeed(speed);
  motorL->setSpeed(0);
  //motorR->run(FORWARD);
  //motorL->run(FORWARD);
  Serial.println("2");
  }

  //if (L_sensor > threshold_L && R_sensor < threshold_R)
  if (diff - ini_diff > 15)
  {
   motorR->setSpeed(0);
   motorL->setSpeed(speed);
   //motorR->run(FORWARD);
   //motorL->run(FORWARD);
   Serial.println("3");
  }
}

