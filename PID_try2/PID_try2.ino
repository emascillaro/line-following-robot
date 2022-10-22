#include <Adafruit_MotorShield.h>
// initiate motor shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// define ports used for motors
Adafruit_DCMotor *motor1 = AFMS.getMotor(2);
Adafruit_DCMotor *motor2 = AFMS.getMotor(4);

// pin setup
int L_sensorPin = A0;
int R_sensorPin = A1;
// initialize variables
int L_speed, R_speed;
int L_sensor, R_sensor;
unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double input, output, setPoint;
double cumError, rateError;
double kp=10,ki=0,kd=0;


void setup() {
  // start serial port and AFMS
  Serial.begin(9600);
  AFMS.begin();
  setPoint = 0;

  pinMode(L_sensorPin,INPUT);
  pinMode(R_sensorPin,INPUT);

  motor1->setSpeed(L_speed);
  motor2->setSpeed(R_speed);
}

void loop() {
  // Take both sensor inputs
  L_sensor = analogRead(L_sensorPin);
  R_sensor = analogRead(R_sensorPin);
  // calculate PID error of the left sensor
  input= L_sensor - R_sensor;
  output = computePID(input);
  //Serial.println("R_sensor");
  //Serial.println(R_sensor);
  //Serial.println("L_sensor");
  //Serial.println(L_sensor);
  Serial.println(output);

  if (output < setPoint + 700)||(output < setPoint - 700)
  {
   motor1->run(FORWARD);
   motor2->run(FORWARD);
   Serial.println("1");
  }
  
  if (output > 700 )
  {
  motor1->setSpeed(150);
  motor1->run(FORWARD);
  motor2->run(FORWARD);
  Serial.println("2");
  }
  if (output > 0)
  {
   motor1->setSpeed(-150);
   motor1->run(FORWARD);
   motor2->run(FORWARD);
   Serial.println("3");
  }
}

  // create PID function that output error
double computePID(double inp){
  // start a timer
  currentTime = millis();
  // how much time has passed since last time
  elapsedTime = currentTime - previousTime;


  error = setPoint - input;
  cumError += error * elapsedTime;
  rateError = (error - lastError)/elapsedTime;

  double out = kp*error + ki*cumError + kd*rateError;
  lastError = error;
  previousTime = currentTime;

  return out;
  Serial.println(out);
}

// function that modifies motor speed based on situation
