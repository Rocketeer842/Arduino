#include <Servo.h>

static const uint8_t A0 = 14;
static const uint8_t A1 = 15;
static const uint8_t A2 = 16;
static const uint8_t A3 = 17;
static const uint8_t A4 = 18;


const int buttonPin = 12;     // the number of the pushbutton pin
const int failSafeButton =  13;      // the number of the failSafeButton pin


const int redPin = 1;
const int bluePin =2;
const int greenPin = 3;


const int timeToWait = 100;
const int targetLbf = 20;
const long runTimeinMillis = 50000;
const float targetMargine = 0.2;

const int incrementAmount = 1;
const unsigned long ServoIdleTime =0;
const unsigned long RunTime =0;
const unsigned long timeNow;


Servo myServo; 

int pos = 0;

// variables will change:
int buttonState = 0, failsafe = 0;         // variable for reading the buttonstate status
boolean isRunning = false;


void setup() {
  pinMode(failSafeButton, INPUT);
  pinMode(buttonPin, INPUT);
  myServo.attach(9); // pin 9 used for the servo 
}


void loop() {
  // read the state of the buttons value:
  timeNow = millis();
  buttonState = digitalRead(buttonPin);
  failsafe = digitalRead(failSafeButton);
  float NDPone = getSensorValue(1,1,A0);
  float NDPtwo = getSensorValue(1,1,A2);
  float lbf = getSensorValue(1,1,A4);

  float pressureRatio = NDPone/NDPtwo;

    Serial.println("\npressureRatio: "+pressureRatio +
      "\nNDP-1: "+NDPone +" psi"+
      "\nNDP-1: "+NDPtwo +" psi" +
      "\nload cell: "+ lbf +" lbf" +
      "\n Servo: "+pos+ " degrees" + 
      "\n Servo: "+pos+ " degrees" 

      );
    // check if failsafe needed
  if(failsafe == HIGH || pressureRatio >= 1.2  ){
    runServoToDegree(0);
    while(true){
      setLedRed();
       delay(1000);  
    }
  }

  // check to see if autonomous performance
  if (buttonState == HIGH) {
    // turn autonomous performance on or off.
    isRunning = !isRunning;
    if(isRunning){
      setLedGreen();
      RunTime = timeNow + runTimeinMillis+250;
    }
    else{
      runServoToDegree(0);
      setLedBlue();   
      RunTime =0;
    }
    delay(250);  
  } 



  // if run time met
  if( RunTime > timeNow){
      isRunning = false;
      runServoToDegree(0);
      setLedBlue();   
  }



if(isRunning && ServoIdleTime < timeNow){
    setLedGreen();
  if(lbf >= targetLbf + targetMargine){

    if(pos < 90)
    {
      pos += incrementAmount;
      runServoToDegree(pos)
    }
  }else if(lbf <= targetLbf - targetMargine){
    if(pos > 0)
    {
      pos -= incrementAmount;
      runServoToDegree(pos)
    }
  }

}else{
  setLedBlue();
}

}

void runServoToDegree(int degree){
  setLedRed();
  int change = abs(pos - degree);
  int waittime = fromDegreesToTimeToWait(change)
  pos = degree;
  myServo.write(degree);
  ServoIdleTime = millis() + waittime;
}

void setLedRed(){
  analogWrite(redPin,255);
  analogWrite(bluePin, 0);
  analogWrite(greenPin, 0);
}

void setLedGreen(){
  analogWrite(redPin,0);
  analogWrite(bluePin, 0);
  analogWrite(greenPin, 255);
}

void setLedBlue(){
  analogWrite(redPin,0);
  analogWrite(bluePin, 255);
  analogWrite(greenPin, 0);
}


void fromDegreesToTimeToWait(int degrees){
  int wait = map(degrees,0,90,0,1500) + 50;

}


float getSensorValue(float m , float b,int pin){

  int sensorValue = analogRead(pin);
  delay(10);
  sensorValue = analogRead(pin);
  // Convert the analog reading  to mV (0 - 5000 mV):
  float miliVoltage = (sensorValue * (5.0 / 1023.0))/1000;  

  float finalValue = m*miliVoltage+b;

  return finalValue;
}