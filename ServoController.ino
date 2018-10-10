#include <Servo.h>


const int buttonPin = 12;     // the number of the pushbutton pin
const int failSafeButton =  13;      // the number of the failSafeButton pin
boolean isRunning = false;

const int redPin = 1;
const int bluePin =2;
const int greenPin = 3;

Servo myServo; 
int pos = 0;

// variables will change:
int buttonState = 0, failsafe = 0;         // variable for reading the buttonstate status

void setup() {
  pinMode(failSafeButton, INPUT);
  pinMode(buttonPin, INPUT);


  myServo.attach(9); // pin 9 used for the servo 
}

void loop() {
  // read the state of the buttons value:
  buttonState = digitalRead(buttonPin);
  failsafe = digitalRead(failSafeButton);

  if(failsafe == HIGH){
    while(true){
       delay(1000);  
    }
  }

  // check to see if autonomous performance
  if (buttonState == HIGH) {
    // turn autonomous performance on or off.
    isRunning = !isRunning;
    if(isRunning)
      setLedGreen();
    else
      setLedBlue();      
    delay(1000);   // waits for a second
         
  } 


if(isRunning){
  // step function
    int currentPSI = getLoadCellValue();
  if(60 > currentPSI >= 40){
      // statement
      runServoToDegree(6);
  } else if(80 > currentPSI >= 60){
        // statement
      runServoToDegree(2);
  } else if( currentPSI >= 80){
        // statement
      runServoToDegree(4);
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
  delay(waittime);
  setLedGreen();
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


int fromDegreesToTimeToWait(int degrees){
  int wait = map(degrees,0,90,0,1500) + 100;
  return wait;
}


int getLoadCellValue(){

  int sensorValue = analogRead(somepine);
  // Convert the analog reading  to mV (0 - 5000 mV):
  float miliVoltage = (sensorValue * (5.0 / 1023.0))/1000;  
  float m = 0.0;
  float b = 0.0;

  float psi = m*miliVoltage+b;

  return psi;
}