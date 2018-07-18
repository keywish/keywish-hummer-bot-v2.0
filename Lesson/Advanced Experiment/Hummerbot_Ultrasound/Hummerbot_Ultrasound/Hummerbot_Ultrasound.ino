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
#include "Ultrasonic.h"
#define INPUT2_PIN 10 // PWMB
#define INPUT1_PIN 6  // DIRB  ---  right
#define INPUT4_PIN 9  // PWMA
#define INPUT3_PIN 5  // DIRA  ---  left
#define SERVO_PIN 13
#define ECHO_PIN 3
#define TRIG_PIN 2
#define INFRARED_AVOIDANCE_LEFT_PIN A3
#define INFRARED_AVOIDANCE_RIGHT_PIN A4
#define IA_THRESHOLD 40
#define UL_LIMIT_MIN 50
#define UL_LIMIT_MID 40
#define UL_LIMIT_MAX 2000
Ultrasonic Ultrasonic(TRIG_PIN, ECHO_PIN, SERVO_PIN);/*Define ultrasonic and servo pins*/

void setup()
{
  Serial.begin(9600);
  pinMode(INFRARED_AVOIDANCE_LEFT_PIN, INPUT);
  pinMode(INFRARED_AVOIDANCE_RIGHT_PIN, INPUT);
  pinMode(INPUT1_PIN, OUTPUT);
  pinMode(INPUT2_PIN, OUTPUT);
  pinMode(INPUT3_PIN, OUTPUT);
  pinMode(INPUT4_PIN, OUTPUT);
  Ultrasonic.SetServoBaseDegree(90);/*Adjust the initial angle of the steering gear according to the steering gear error*/
  Ultrasonic.SetServoDegree(90);/*Set the servo angle*/
}

void loop()
{
  uint16_t RightValue, LeftValue;
  uint16_t UlFrontDistance, UlLeftDistance, UlRightDistance;
  RightValue = analogRead(INFRARED_AVOIDANCE_RIGHT_PIN);/*The infrared obstacle avoidance module collects the left data*/
  LeftValue = analogRead(INFRARED_AVOIDANCE_LEFT_PIN);/*The infrared obstacle avoidance module collects the right data*/
  UlFrontDistance = Ultrasonic.GetUltrasonicFrontDistance();/*The ultrasonic module collects the front data*/
  if (((RightValue > IA_THRESHOLD) && (LeftValue > IA_THRESHOLD)) && ((UlFrontDistance > UL_LIMIT_MID) && (UlFrontDistance < UL_LIMIT_MAX)))
  /*According to the data collected by the ultrasonic module and the infrared obstacle avoidance module,
    it is judged whether there is an obstacle in front, and if there is no obstacle, go straight.*/
  {
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT1_PIN, 200);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, 200);
  }
  else if ((RightValue > IA_THRESHOLD) && (LeftValue < IA_THRESHOLD))
  /*The data collected by the infrared obstacle avoidance module determines whether there is an obstacle on the right side. If not, turn right.*/
  {
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT1_PIN, 150);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, 0);
    delay(200);
  }
  else if ((RightValue < IA_THRESHOLD) && (LeftValue > IA_THRESHOLD))
  /*The data collected by the infrared obstacle avoidance module determines whether there is an obstacle on the left side. If not, turn left.*/
  {
    analogWrite(INPUT2_PIN, 0);
    analogWrite (INPUT1_PIN, 0);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, 150);
    delay(200);
  }
  else if ((RightValue < IA_THRESHOLD) && (LeftValue < IA_THRESHOLD))
  /*The data collected by the infrared obstacle avoidance module determines whether there are obstacles on the left and right sides, if any, rotates 180 degrees.*/
  {
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT1_PIN, 150);
    analogWrite(INPUT3_PIN, 150);
    analogWrite(INPUT4_PIN, 0);
    delay(150);
  }
  else if (((RightValue > IA_THRESHOLD) && (LeftValue > IA_THRESHOLD)) && ((UlFrontDistance < UL_LIMIT_MID) || (UlFrontDistance > UL_LIMIT_MAX)))
  /*According to the data collected by the ultrasonic module and the infrared obstacle avoidance module, it is determined whether there is an obstacle in front. For example, 
   * the infrared obstacle avoidance module determines that there is no obstacle in front, and the ultrasonic module determines that the right obstacle is an obstacle, 
   * first stops the car, and uses the ultrasonic module to perform left and right.*/
  {
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT1_PIN, 0);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, 0);
    Ultrasonic.SetServoDegree(0);/*Servo rotation to 0 degrees*/
    UlRightDistance = Ultrasonic.GetUltrasonicRightDistance();/*The ultrasonic module collects the right side*/
    Ultrasonic.SetServoDegree(180);/*Servo rotation to 180 degrees*/
    UlLeftDistance = Ultrasonic.GetUltrasonicLeftDistance();/*The ultrasonic module collects the left side*/
    if ((UlRightDistance > UL_LIMIT_MIN) && (UlRightDistance < UL_LIMIT_MAX) && (UlRightDistance > UlLeftDistance))
    /*According to the ultrasonic module to collect the data on the left and right sides to determine whether there is an obstacle on the right side.*/
    {
      analogWrite(INPUT2_PIN, 0);
      analogWrite(INPUT1_PIN, 150);
      analogWrite(INPUT3_PIN, 0);
      analogWrite(INPUT4_PIN, 0);
      delay(200);
    }
    else if ((UlLeftDistance > UL_LIMIT_MIN) && (UlLeftDistance < UL_LIMIT_MAX) && (UlLeftDistance > UlRightDistance))
   /*According to the ultrasonic module to collect the data on the left and right sides to determine whether there is an obstacle on the left side.*/
    {
      analogWrite(INPUT2_PIN, 0);
      analogWrite (INPUT1_PIN, 0);
      analogWrite(INPUT3_PIN, 0);
      analogWrite(INPUT4_PIN, 150);
      delay(200);
    }
    else if ((UlRightDistance < UL_LIMIT_MIN) && (UlLeftDistance < UL_LIMIT_MIN) )
    /*According to the ultrasonic module to collect the data on the left and right sides to determine whether there are obstacles on the left and right sides*/
    {
      analogWrite(INPUT2_PIN, 0);
      analogWrite(INPUT1_PIN, 150);
      analogWrite(INPUT3_PIN, 150);
      analogWrite(INPUT4_PIN, 0);
      delay(300);
    }
  }
}
