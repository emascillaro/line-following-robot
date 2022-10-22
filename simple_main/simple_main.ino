#include <Adafruit_MotorShield.h>

int threshold = 700;
int L_sensorPin = A0;
int R_sensorPin = A1;

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define which ports are used for motors
Adafruit_DCMotor *motor1 = AFMS.getMotor(2);
Adafruit_DCMotor *motor2 = AFMS.getMotor(4);

void setup() {
  // put your setup code here, to run once:
  //AFMS.begin(uint16_t freq=1600);
  Serial.begin(9600);
  AFMS.begin();  // create with the default frequency 1.6KHz
  //Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
  //Adafruit_DCMotor *motor2 = AFMS.getMotor(1);

  // Set speed & Direction for motors
  motor1->setSpeed(0);
  motor2->setSpeed(0);

  pinMode(L_sensorPin,INPUT);
  pinMode(R_sensorPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float L_sensor = analogRead(L_sensorPin);
  float R_sensor = analogRead(R_sensorPin);

  Serial.println("nothing");
  if (L_sensor > threshold && R_sensor > threshold)
  {
   motor1->run(FORWARD);
   motor2->run(FORWARD);
   Serial.println(L_sensor);
  }
  if (L_sensor < threshold && R_sensor < threshold)
  {
    motor1->run(FORWARD);
    motor2->run(FORWARD);
   Serial.println(L_sensor);
  }
  if (L_sensor < threshold && R_sensor > threshold)
  {
   motor1->setSpeed(255);
   motor1->run(FORWARD);
   motor2->run(FORWARD);
   Serial.println("3");
  }
  if (L_sensor > threshold && R_sensor < threshold)
  {
    motor1->run(FORWARD);
    motor2->setSpeed(-30);
    motor2->run(FORWARD);
   Serial.println("4");
  }
}
