#include <Servo.h>  // add servo library

Servo myservo;  // create servo object to control a servo

int button1 = 4;  // analog pin used to connect the potentiometer
int button2 = 3;
int b1;    // variable to read the value from the analog pin
int b2;
int i;
int latch;
int time;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  i = 0;
  latch = 0;
  myservo.write(0);
  digitalWrite(5, 1);
  time = 5000;
}

void loop() {
  b1 = digitalRead(button1);            // reads the value of the button 1 or 0 (0 pressed)
  b2 = digitalRead(button2);            // reads the value of the button 1 or 0 (0 pressed)
/*
  for(i=0; i>10; i++)
  {
  int sensorVal=analogRead(A1);
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);
  
  float voltage = (voltage - 0.5) * (100.0) / (4.5 - 0.5);
    Serial.print("Volts: ");
    Serial.print(voltage);
   
  float pressure_pascal = (3.0*((float)voltage-0.47))*1000000.0;
  float pressure_psi = pressure_pascal/10e5;
    Serial.print("Pressure = ");
    Serial.print(pressure_psi);
    Serial.println(" psi");
    Serial.print("Pressure = ");
  }
  */

  if(!b1){
    for(int t=0; t<time; t++){
      if(b2)
      myservo.write(70);
      else
      myservo.write(0);
    }
    digitalWrite(5, 0);
    digitalWrite(6, 1);
    delay(2000);
    digitalWrite(6, 0);
    digitalWrite(7, 1);
       
  }
  if(!b2){
    myservo.write(0);
    digitalWrite(7, 0);
    digitalWrite(6, 1);
    delay(2000);
    digitalWrite(6, 0);
    digitalWrite(5, 1);
  }
  
  delay(15);                           // waits for the servo to get there
  Serial.println(b1);
  Serial.print(b2);
  
}
