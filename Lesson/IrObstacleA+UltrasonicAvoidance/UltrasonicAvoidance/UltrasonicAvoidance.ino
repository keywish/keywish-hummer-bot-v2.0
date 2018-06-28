/***********************************************************************
 *       __                                                          _
 *      / /        _____  __    __  _          _   (_)   ________   | |
 *     / /____   / _____) \ \  / / | |   __   | |  | |  (  ______)  | |_____
 *    / / ___/  | |_____   \ \/ /  | |  /  \  | |  | |  | |______   |  ___  |
 *   / /\ \     | |_____|   \  /   | | / /\ \ | |  | |  (_______ )  | |   | |
 *  / /  \ \__  | |_____    / /    | |/ /  \ \| |  | |   ______| |  | |   | |
 * /_/    \___\  \______)  /_/      \__/    \__/   |_|  (________)  |_|   |_|
 *
 *
 * KeyWay Tech firmware
 *
 * Copyright (C) 2015-2020
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, in version 3.
 * learn more you can see <http://www.gnu.org/licenses/>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "Servo.h"
Servo head;

int E1 = 5; //PWMA
int M1 = 9; //DIRA****************************************left
int E2 = 6; //PWMB
int M2 = 10; //DIRB****************************************right
const int TrigPin = 2;
const int EchoPin = 3;
const int leftPin = A3;
const int rightPin = A4;
float da;
float dl;
float dr;
float left;
float right;
void setup()
{
  Serial.begin(9600);
  head.attach(13);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  head.write(80);
  delay(1000);
}

void loop()
{
   
  left = analogRead(leftPin);
  right = analogRead(rightPin);   
  analogWrite(TrigPin, 0); //Send a short pulse to TrigPin
  delayMicroseconds(2);
  analogWrite(TrigPin, 255);
  delayMicroseconds(10);
  analogWrite(TrigPin, 0);
  da = pulseIn(EchoPin, HIGH) / 58.0; //The echo time is converted to cm

  if ((da >= 50) && (da <= 2000)&&(left>= 38)&&(right>= 38))
   {
     int val=150;
     analogWrite(M1,0);
     analogWrite(E1, val); //the speed value of motorA is 255
     analogWrite(M2,0);
     analogWrite(E2, val); //the speed value of motorB is 255
     Serial.print("Distance = ");
     Serial.print(da);
     Serial.print("    ");
     Serial.println("Moving advance 50");
    // delay(500);          //If the distance is greater than 20cm then go forward and output "is moving forward"
   }
   if ((da <40)&& (da >30)&&(left>= 38)&&(right>= 38))
   {
     int val=130;
     analogWrite(M1,0);
     analogWrite(E1, val); //the speed value of motorA is 255
     analogWrite(M2,0);
     analogWrite(E2, val); //the speed value of motorB is 255
     Serial.print("Distance = ");
     Serial.print(da);
     Serial.print("    ");
     Serial.println("Moving advance40");
   //  delay(500);
   }
    if ((left <= 38) && (right >= 38) && (da >= 30 && da <= 1000))
  {
   digitalWrite(M1,HIGH);
   analogWrite(E1,0); //the speed value of motorA is val
   analogWrite(M2,0);
   analogWrite(E2, 250); //the speed value of motorA is val
   Serial.println("Turning right");
   delay(200);
   analogWrite(M1,0);
   analogWrite(E1, 0);
   analogWrite(M2,0);
   analogWrite(E2, 0);
   //delay(1000); //********************************************//Turning right
  }
   if ((left >= 38) && (right <=38) && (da >= 30 && da <= 1000))
  {
   analogWrite(M1,0);
   analogWrite(E1, 250); //the speed value of motorA is 180
   digitalWrite(M2,HIGH);
   analogWrite(E2, 0); //the speed value of motorB is 180
   Serial.println("Turning left");
   delay(200);
   analogWrite(M1,0);
   analogWrite(E1, 0);
   analogWrite(M2,0);
   analogWrite(E2, 0);
  // delay(1000); //********************************************//Turning left
  }

   else if (da <= 25)
   {
     int val=0;
     analogWrite(M1,0);
     analogWrite(E1, val); //the speed value of motorA is 255
     analogWrite(M2,0);
     analogWrite(E2, val); //the speed value of motorB is 255
     Serial.print("Distance = ");
     Serial.print(da);
     Serial.print("    ");
     Serial.println("Stopped");//If the distance is less than 20cm, the car stops and outputs "stopped"
     delay(500);
     head.write(180);
     delay(1000);
     analogWrite(TrigPin, 0); //Send a short pulse to TrigPin
     delayMicroseconds(2);
     analogWrite(TrigPin, 255);
     delayMicroseconds(10);
     analogWrite(TrigPin, 0);
     dl = pulseIn(EchoPin, HIGH) / 58.0; //The echo time is converted to cm
     Serial.print("Left distance = ");
     Serial.print(dl);
     Serial.print("  ");
     //Turn the left steering wheel to the left to measure the distance and output
     head.write(0);
     delay(1000);
     analogWrite(TrigPin, 0); 
     delayMicroseconds(2);
     analogWrite(TrigPin, 255);
     delayMicroseconds(10);
     analogWrite(TrigPin, 0);
     dr = pulseIn(EchoPin, HIGH) / 58.0; 
     Serial.print("Right distance = ");
     Serial.print(dr);
     Serial.print("  ");
     Serial.println();
     //Head rudder turn right to measure the right distance and output
     head.write(80);     //Head steering gear back
     if (dl >= 20 && dl <= 1000 && dl > dr)
     {
       analogWrite(M1,0); 
       analogWrite(E1, 180); //the speed value of motorA is 255
       digitalWrite(M2,1);
       analogWrite(E2, 0); //the speed value of motorB is 255
       Serial.println("Turning left1");
       delay(200);      //To determine the left and right distance left if the larger
      }
     else if (dl >= 1000)
    {
      digitalWrite(M1,1);
      analogWrite(E1, 0); //the speed value of motorA is 255
      analogWrite(M2,0);
      analogWrite(E2, 180); //the speed value of motorB is 255
      Serial.println("Turning right1");
      delay(200);
      //Special circumstances if the left to return distance greater than 1000 shows the probe is blocked at this time turn right
      }
     else if (dr >= 20 && dr <= 1000 && dr > dl)
    {
      digitalWrite(M1,1);
      analogWrite(E1, 0); //the speed value of motorA is 255
      analogWrite(M2,0);
      analogWrite(E2, 180); //the speed value of motorB is 255
      Serial.println("Turning right2");
      delay(200);      //判断左右距离 若右边大则右转
    }
     else if (dr >= 1000)
   {
     analogWrite(M1,0);
     analogWrite(E1, 180); //the speed value of motorA is 255
     digitalWrite(M2,1);
     analogWrite(E2, 0); //the speed value of motorB is 255
     Serial.println("Turning left2");
     delay(200);
     //Special circumstances if the right to return distance greater than 1000 shows the probe is blocked at this time turn left
    }
   else if (dr <= 20 && dl <= 20)
  {
    digitalWrite(M1,1);
    analogWrite(E1, 0); //the speed value of motorA is 255
    analogWrite(M2,0);
    analogWrite(E2, 255); //the speed value of motorB is 255
    Serial.println("Turning around");
    delay(700);
    //If the left and right sides are less than 20cm, then turn around
   }
 }
}
