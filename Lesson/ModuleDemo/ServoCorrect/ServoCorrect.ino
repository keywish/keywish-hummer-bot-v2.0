#include <Servo.h>
Servo myservo;// create servo object to control a servo
int pos = 90; // variable to store the servo position
void setup() {
  myservo.attach(13);// attaches the servo on pin 13 to the servo object
}

void loop() {
  myservo.write(pos);// tell servo to go to position in variable 'pos'
  delay(15);// waits 15ms for the servo to reach the position
}

