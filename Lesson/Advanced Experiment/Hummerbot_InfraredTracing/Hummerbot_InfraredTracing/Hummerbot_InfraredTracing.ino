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
int INPUT3_PIN = 5; //PWMA
int INPUT4_PIN = 9; //DIRA****************************************left
int INPUT1_PIN = 6; //PWMB
int INPUT2_PIN = 10; //DIRB****************************************right
/*Define 4 motor control terminals, connected to IN1-IN4 on the motor drive board.*/
void setup() {
  Serial.begin(9600); /*Set the baud rate to 9600 */
  Serial.println("Get last update from https://github.com/keywish/keywish-beetle-bot");
}
void loop()
{
  int left, centre, right; /*Define 3 sensors */
  left = analogRead(A0);
  centre = analogRead(A1);
  right = analogRead(A2); /*Read the value collected by 3 sensors */
  Serial.println(centre);
  if ((right >= 975) && (centre <= 8) && (left >= 975)) {
    /* Judge the collected value, if right > the sensor captures a value that is low and reads 0 after analog IO. However, to reduce the error, we set the threshold In 8, to prevent the error caused by the car to determine the wrong, we can
      customize the other values, if the use of digital port to receive the value of the sensor returns only "0" and "1", but to determine the same way. The reason why I did not use digital IO, because we use the digital IO port in other places. */
    int value = 150; /*Set a PWM value, the maximum value of PWM is 255, but the speed should not be too fast when tracing the car, otherwise the car will shake more in the tracing process.*/
    analogWrite (INPUT4_PIN, 0);
    analogWrite(INPUT3_PIN, value); //the speed value of motorA is value
    analogWrite (INPUT2_PIN, 0);
    analogWrite(INPUT1_PIN, value); //the speed value of motorB is value
  }
  else if ((right <= 8) && (centre >= 975) && (left >= 975)) { /* The value collected to judge, if the center > = 975 and left > = 975 are greater than 975, indicating that the middle and left sensors did not detect the black line, right <= 8 shows the right sensor detects a black line, then the car Has left to the left, or the black line has been turning to the right, so the car should turn to the right. */
    analogWrite (INPUT3_PIN, 180);
    analogWrite(INPUT4_PIN, 0); //the speed value of motorA is value
    analogWrite (INPUT2_PIN, 0);
    analogWrite(INPUT1_PIN, 0); //the speed value of motorB is value
  }
  else if ((right >= 975) && (centre >= 975) && (left <= 8)) { /* Judge the collected value, if center > = 975 and right > = 975 are greater than 975, indicating that the middle and right sensors did not detect the black line, left <= 8 shows that the left sensor detects the black line, then the car Has been to the right deviation, or the black line has turned to the left, so the car should turn left at this time. */
    int value = 130;
    analogWrite (INPUT4_PIN, 0);
    analogWrite(INPUT3_PIN, 0); //the speed value of motorA is value
    analogWrite (INPUT1_PIN, value);
    analogWrite(INPUT2_PIN, 0); //the speed value of motorB is value
  }
  if ((right <= 8) && (centre <= 8) && (left <= 8)) {/* The value collected to judge, if the center <= 8, left <= 8 and right <= 8 are greater than 8, indicating 3 sensors have detected a black line, then the car has reached the "ten" intersection, because We have only 3 sensors, no way to make more sophisticated judgments, so only let the car choose to go straight. */
    int value = 130;
    analogWrite (INPUT4_PIN, 0);
    analogWrite(INPUT3_PIN, value); //the speed value of motorA is value
    analogWrite (INPUT2_PIN, 0);
    analogWrite(INPUT1_PIN, value); //the speed value of motorB is value
  }
}

