/***********************************************************************
         __                                                          _
        / /        _____  __    __  _          _   (_)   ________   | |
       / /____   / _____) \ \  / / | |   __   | |  | |  (  ______)  | |_____
      / / ___/  | |_____   \ \/ /  | |  /  \  | |  | |  | |______   |  ___  |
     / /\ \     | |_____|   \  /   | | / /\ \ | |  | |  (_______ )  | |   | |
    / /  \ \__  | |_____    / /    | |/ /  \ \| |  | |   ______| |  | |   | |
   /_/    \___\  \______)  /_/      \__/    \__/   |_|  (________)  |_|   |_|


   KeyWay Tech firmware

   Copyright (C) 2015-2020

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation, in version 3.
   learn more you can see <http://www.gnu.org/licenses/>.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.

*/
int INPUT3_PIN = 5; //PWMA
int INPUT4_PIN = 9; //PWMA
int INPUT1_PIN = 6; //PWMB
int INPUT2_PIN = 10; //PWMB
void setup() {
  Serial.begin(9600);
  pinMode(INPUT3_PIN, OUTPUT);
  digitalWrite(INPUT3_PIN, LOW); // When not sending PWM, we want it low
  pinMode(INPUT4_PIN, OUTPUT);
  digitalWrite(INPUT4_PIN, LOW); // When not sending PWM, we want it low
  pinMode(INPUT1_PIN, OUTPUT);
  digitalWrite(INPUT1_PIN, LOW); // When not sending PWM, we want it low
  pinMode(INPUT2_PIN, OUTPUT);
  digitalWrite(INPUT2_PIN, LOW); // When not sending PWM, we want it low
}

void loop() {
  analogWrite(INPUT2_PIN, 0);
  analogWrite(INPUT1_PIN, 200);//the speed value of motorA is 200
  analogWrite(INPUT3_PIN, 200);
  analogWrite(INPUT4_PIN, 0);//the speed value of motorB is 200
  delay(5000);
  //******** ******************************//forward
  analogWrite(INPUT2_PIN, 0);
  analogWrite(INPUT1_PIN, 0); //the speed value of motorA is 0
  analogWrite(INPUT3_PIN, 0);
  analogWrite(INPUT4_PIN, 0); //the speed value of motorB is 0
  delay(1000);//********************************************//stop
  analogWrite(INPUT2_PIN, 200);//the speed value of motorA is 200
  analogWrite(INPUT1_PIN, 0);
  analogWrite(INPUT3_PIN, 0);//the speed value of motorB is 200
  analogWrite(INPUT4_PIN, 200);
  delay(5000);//*********************************************//back
  analogWrite(INPUT4_PIN, 0);
  analogWrite(INPUT3_PIN, 0); //the speed value of motorA is 0
  analogWrite(INPUT2_PIN, 0);
  analogWrite(INPUT1_PIN, 0); //the speed value of motorB is 0
  delay(1000);
  //******* ***************************************//stop
  analogWrite(INPUT2_PIN, 0);
  analogWrite(INPUT1_PIN, 150);
  analogWrite(INPUT3_PIN, 0);
  analogWrite(INPUT4_PIN, 0);//the speed value of motorA is 150
  delay(3000);
  //*******************************************//left
  analogWrite(INPUT2_PIN, 0);
  analogWrite(INPUT1_PIN, 0); //the speed value of motorA is 0
  analogWrite(INPUT3_PIN, 0);
  analogWrite(INPUT4_PIN, 0); //the speed value of motorB is 0
  delay(1000); //*******************************************//stop
  analogWrite(INPUT2_PIN, 0);
  analogWrite(INPUT1_PIN, 0);//the speed value of motorB is 150
  analogWrite(INPUT3_PIN, 150);
  analogWrite(INPUT4_PIN, 0);
  delay(3000);//*** ***************************************//right
}
