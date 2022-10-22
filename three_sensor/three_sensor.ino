#include <Adafruit_MotorShield.h>
// initiate motor shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// define ports used for motors
Adafruit_DCMotor *motorR = AFMS.getMotor(2);
Adafruit_DCMotor *motorL = AFMS.getMotor(4);

// pin setup
int L_sensorPin = A0;
int R_sensorPin = A1;
int M_sensorPin = A2;

// initialize variables
int L_sensor, R_sensor, M_sensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  AFMS.begin();

  pinMode(L_sensorPin,INPUT);
  pinMode(R_sensorPin,INPUT);
  pinMode(M_sensorPin,INPUT);

  motorR->setSpeed(0);
  motorL->setSpeed(0);

  L_sensor = analogRead(L_sensorPin);
  R_sensor = analogRead(R_sensorPin);
  M_sensor = analogRead(M_sensorPin);

  while (Serial.available() == 0){}

  motorR->run(FORWARD);
  motorL->run(FORWARD);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  L_sensor = analogRead(L_sensorPin);
  R_sensor = analogRead(R_sensorPin);
  M_sensor = analogRead(M_sensorPin);
  int L_diff = L_sensor - M_sensor;
  int R_diff = R_sensor - M_sensor;

  motorR->setSpeed(40);
  motorL->setSpeed(40);

// normal adjustment
if(M_sensor < 0){
  if(L_diff >= 0 && L_diff <= 100){
  motorR->setSpeed(20 + L_diff * 0.2);
  motorL->setSpeed(5);
  
  Serial.println("too right");
  }
  
  
  if(R_diff >= 0 && R_diff <= 100){
  motorL->setSpeed(20 + R_diff * 0.2);
  motorR->setSpeed(5);
  Serial.println("too left");

  if(L_diff > 100){
  motorR->setSpeed(L_diff * 0.15);
  motorL->setSpeed(1);
  
  Serial.println("toooooo right!");
  }

  if(R_diff > 100){
  motorL->setSpeed(R_diff * 0.15);
  motorR->setSpeed(1);
  
  Serial.println("tooooo left!");
  }
  }

  else{ 
    Serial.println("Good enough");
  }
}
else 
    Serial.println("On track");
}
