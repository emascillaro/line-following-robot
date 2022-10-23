#include <Adafruit_MotorShield.h>

// initiate motor shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// define ports used for motors
Adafruit_DCMotor *motorR = AFMS.getMotor(2);
Adafruit_DCMotor *motorL = AFMS.getMotor(4);

// pin setup
int LSensorPin = A0; // A0: left sensor
int RSensorPin = A1; // A1: right sensor
int button = 8; // Digital pin 8: button

// initialize variables
int LSensor, RSensor;
int Lspeed, Rspeed;
int speed = 0; // initial speed
int Kp = 1; // Proportional control coefficient
int threshold = 940; // sensor value when too close to track
int counter = 0; // button state counter

enum states {FAST, SLOW}; // two states of speed
states state;


// variables for button bounce
long currentTime = 0;
unsigned long debounceDuration = 10; // unit: millisecond
unsigned long lastTime = 0;
unsigned long timerOne = 0;
unsigned long timerTwo = 0;
byte previousState = LOW;


void setup() {
  // start serial port and AFMS
  Serial.begin(9600);
  AFMS.begin();

  // Initiate IR sensors and button
  pinMode(LSensorPin,INPUT);
  pinMode(RSensorPin,INPUT);
  pinMode(button,INPUT);

  // Set initial motor speeds to 0
  motorR->setSpeed(0);
  motorL->setSpeed(0);

  // set car to drive straight
  motorR->run(FORWARD);
  motorL->run(FORWARD);

}

void loop() {
  // Find time now
  currentTime = millis();

  // Make sure no bounce is counted
  if(currentTime > lastTime + debounceDuration){
    byte currentState = digitalRead(button);

    // If no change in button state
    if (currentState == previousState){
      running();
    }

    // If button is pushed
    if(currentState != previousState){
      previousState = currentState;
      lastTime = millis();

      Serial.println("Press button: 1-slow; 2-fast");

    // change state based on button click
      if (currentState == LOW){
        // record everytime button high->low
        counter++;
        // state: fast mode (speed: 35)
        if(counter % 2 == 1){state = FAST;}
        // state: slow mode (speed: 27)
        if(counter % 2 == 0){state = SLOW;}
      }
    }
  }

// counter = 0: car not moving
// counter = odd: fast state
// counter = even: slow state
if(counter > 0){
  switch(state){
  case FAST:
    motorR->setSpeed(35);
    motorL->setSpeed(35);
    running();

  case SLOW:
    motorR->setSpeed(27);
    motorL->setSpeed(27);
    running();
  } 
}
}

// main function for car moving forward
void running(){

  // Take both sensor inputs
  LSensor = analogRead(LSensorPin);
  RSensor = analogRead(RSensorPin);

  // Car drives straight if both sensors are off the line
  if (LSensor < threshold && RSensor < threshold)
  {
  //Serial.println("Driving straight!");
  }
  
  // Car turns left if left sensor is on the line
  if (LSensor > threshold && RSensor < threshold)
  {
  
  // Set motor speeds
  Rspeed = speed + (LSensor - 930) * Kp;
  motorR->setSpeed(Rspeed); 
  motorL->setSpeed(0); 

  }

  // Car turns right if right sensor is on the line
  if (LSensor < threshold && RSensor > threshold)
  {
   
  // Set motor speeds
  Lspeed = speed + (RSensor - 930) * Kp;
  motorR->setSpeed(0);  
  motorL->setSpeed(Lspeed); 

  }
 
  Serial.print(RSensor);
  Serial.print( "/" );
  Serial.println(Lspeed);
}
