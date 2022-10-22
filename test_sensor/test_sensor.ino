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
  L_sensor = analogRead(L_sensorPin);
  R_sensor = analogRead(R_sensorPin);
  M_sensor = analogRead(M_sensorPin);

}

void loop() {
  while(Serial.available() ==0) {}
  // put your main code here, to run repeatedly:
  L_sensor = analogRead(L_sensorPin);
  R_sensor = analogRead(R_sensorPin);
  M_sensor = analogRead(M_sensorPin);

  int L_diff = L_sensor - M_sensor;
  int R_diff = R_sensor - M_sensor;

  Serial.println(L_diff);
  //Serial.println(R_diff);

}
