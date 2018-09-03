#include <Servo.h>  // add servo library

Servo myservo;  // create servo object to control a servo

int button1 = 4;  // analog pin used to connect the potentiometer
int button2 = 3;
int b1;    // variable to read the value from the analog pin
int b2;
int i;
int latch;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  i = 0;
  latch = 0;
  myservo.write(0);
  digitalWrite(5, 1);
}

void loop() {
  b1 = digitalRead(button1);            // reads the value of the button 1 or 0 (0 pressed)
  b2 = digitalRead(button2);            // reads the value of the button 1 or 0 (0 pressed)


  if(!b1){
    myservo.write(70);
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
