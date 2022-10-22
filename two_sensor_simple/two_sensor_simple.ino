#include <Adafruit_MotorShield.h>
// initiate motor shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// define ports used for motors
Adafruit_DCMotor *motorR = AFMS.getMotor(2);
Adafruit_DCMotor *motorL = AFMS.getMotor(4);

// pin setup
int LSensorPin = A0;
int RSensorPin = A1;

// initialize variables
int LSensor, RSensor;
String input;
int speed = 40;


void setup() {
  // start serial port and AFMS
  Serial.begin(9600);
  AFMS.begin();

  // Initiate IR sensors as inputs
  pinMode(LSensorPin,INPUT);
  pinMode(RSensorPin,INPUT);

  // Set initial motor speeds to 0
  motorR->setSpeed(0);
  motorL->setSpeed(0);

  // Read Sensor Values
  LSensor = analogRead(LSensorPin);
  RSensor = analogRead(RSensorPin);

}

void loop() {
  
  // Take both sensor inputs
  LSensor = analogRead(LSensorPin);
  RSensor = analogRead(RSensorPin);

  Serial.println("LSensor: ");
  Serial.println(LSensor);

  Serial.println("RSensor: ");
  Serial.println(RSensor);

  // Car drives straight if both sensors are off the line
  if (LSensor < 900 and RSensor < 900)
  {
   
  // Set motor speeds
  motorR->setSpeed(speed);  
  motorL->setSpeed(speed); 
  
  // Have car drive straight
  motorR->run(FORWARD);
  motorL->run(FORWARD);

  Serial.println("driving straight");
  }
  
  // Car turns left if left sensor is on the line
  if (LSensor > 900 and RSensor < 900)
  {
   
  // Set motor speeds
  motorR->setSpeed(speed);  
  motorL->setSpeed(0); 
  
  // Have car drive straight
  motorR->run(FORWARD);
  motorL->run(FORWARD);

  Serial.println("turning left");
  }

  // Car turns right if right sensor is on the line
  if (LSensor < 900 and RSensor > 900)
  {
   
  // Set motor speeds
  motorR->setSpeed(0);  
  motorL->setSpeed(speed); 
  
  // Have car drive straight
  motorR->run(FORWARD);
  motorL->run(FORWARD);

  Serial.println("turning right");
  }
}

