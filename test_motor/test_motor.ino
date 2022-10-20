#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define which ports are used for motors
Adafruit_DCMotor *motor1 = AFMS.getMotor(2);
Adafruit_DCMotor *motor2 = AFMS.getMotor(4);

void setup() {
  Serial.begin(9600);
  AFMS.begin();  // create with the default frequency 1.6KHz
  Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
  Adafruit_DCMotor *motor2 = AFMS.getMotor(1);

  // Set speed & Direction for motors
  motor1->setSpeed(50);
  motor2->setSpeed(50);
}

void loop() {
   motor1->run(FORWARD);
   motor2->run(FORWARD);

}
