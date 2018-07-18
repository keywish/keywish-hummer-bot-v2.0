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
int INPUT4_PIN = 9; //DIRA****************************************Right
int INPUT1_PIN = 6; //PWMB
int INPUT2_PIN = 10 ; //DIRB****************************************Left 
/*Define 4 motor control terminals, connected to IN1-IN4 on the motor RightValueive board。*/
const int leftPin = A3;
const int rightPin  = A4; // Define the two signal receiving ends of the sensor
float LeftValue;
float RightValue;// Define two margins to store the values read by both sensors

void setup() {
  Serial.begin(9600); // Set the serial port baud rate to 9600,
  Serial.println("Get last update from https://github.com/keywish/keywish-beetle-bot");
  pinMode(leftPin, INPUT);
  pinMode(rightPin , INPUT);// Set the working mode of two sensor pins, namely "input"
  digitalWrite(INPUT3_PIN, LOW); // When not sending PWM, we want it low
  pinMode(INPUT4_PIN, OUTPUT);
  digitalWrite(INPUT4_PIN, LOW); // When not sending PWM, we want it low
  pinMode(INPUT1_PIN, OUTPUT);
  digitalWrite(INPUT1_PIN, LOW); // When not sending PWM, we want it low
  pinMode(INPUT2_PIN, OUTPUT);
  digitalWrite(INPUT2_PIN, LOW); // When not sending PWM, we want it low
  delay(1000);
}

void loop() {
  LeftValue = analogRead(leftPin);
  RightValue = analogRead(rightPin ); // Read the values collected by both sensors and assign them to the defined variables。
  if (LeftValue >= 38 && RightValue <= 38) {/*If the value collected by the left sensor is greater than or equal to 38 and the RightValue value is less than or equal to 38, the following program in {} is executed (LeftValue> = 38, there is no obstacle on the left, RightValue<= 38 shows that there is an obstacle on the RightValue, so at this time the car is turning to the side without obstacles (ie, turning to the left). From Figure 3.2.11, we know that the simulated value will RightValueop below about 35 in the event of an obstacle , But in order to reduce the error, we set the threshold at 38 to prevent the car from judging the error because of the error. We can also customize other values. If we use the digital port to receive the value of the sensor, we only return "0" and "1" ", But the same way to judge. The reason why I did not use digital IO, because we use the digital IO port in other places.*/
    analogWrite (INPUT4_PIN, 0);
    analogWrite(INPUT3_PIN, 0); 
    analogWrite (INPUT2_PIN, 0); 
    analogWrite(INPUT1_PIN, 180); /*Set a PWM value, the maximum PWM is 255, but the speed of the car should not be too fast when walking, otherwise it can not hit the obstacle in time when the obstacles are suddenly encountered.*/
    Serial.print(LeftValue);
    Serial.print("   ");
    Serial.print(RightValue);
    Serial.print("   ");
    Serial.println("Turning left"); /*Through the "Serial Monitor" print the current status of the car and the value collected by the sensor*/
    delay(300);
    analogWrite(INPUT4_PIN, 0);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT1_PIN, 0); 
    delay(1000);//************************************//Turning left
  }

  if (LeftValue <= 38 && RightValue <= 38) {/*If the value collected by the left sensor is less than or equal to 38 and the RightValue value is less than or equal to 38, the following program in {} is executed (LeftValue <= 38, indicating that there is an obstacle on the left and RightValue<= 38 shows that there is an obstacle on the RightValue, so at this time the car is rotated 180 degrees backwards. In the experiment, the car can just turn around 180 degrees after 500ms of rotation. Because the DC motor can not precisely control the angle like the steering gear, An approximate value, of course, different motor speed is not the same, the time used is not the same, so everyone in the experiment can be based on the circumstances may be.)*/
    analogWrite(INPUT4_PIN, 0); 
    analogWrite(INPUT3_PIN, 255);
    analogWrite(INPUT2_PIN, 255);
    analogWrite(INPUT1_PIN, 0); 
    Serial.print(LeftValue);
    Serial.print("   ");
    Serial.print(RightValue);
    Serial.print("   ");
    Serial.println("Turning around");/*Through the "Serial Monitor" print the current status of the car and the value collected by the sensor.*/
    delay(500);
    analogWrite (INPUT4_PIN, 0);
    analogWrite (INPUT3_PIN, 0);
    analogWrite (INPUT2_PIN, 0);
    analogWrite (INPUT1_PIN, 0); /*Rotate 180 degrees and stop*/
    delay(1000);//*********************************//Turning around
  }
  if (LeftValue <= 38 && RightValue >= 38) /*If the left sensor is less than or equal to 38 and the RightValue value is greater than or equal to 38, the following program in {} is executed (LeftValue <= 38, indicating that there is an obstacle on the left, RightValue> = 38 shows that there is no obstacle on the left, so at this moment the car is turning to the side without obstacle, that is, turning to the RightValue)*/
  {
    analogWrite(INPUT4_PIN, 0);//the speed value of motorA is val
    analogWrite(INPUT3_PIN, 180);
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT1_PIN, 0);//the speed value of motorA is val
    Serial.print(LeftValue);
    Serial.print("   ");
    Serial.print(RightValue);
    Serial.print("   ");
    Serial.println("Turning RightValue");
    delay(300);
    analogWrite(INPUT4_PIN, 0);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT1_PIN, 0);/*Car must stop after each rotation, if you do not stop there will be the phenomenon of rotating around. */
    delay(1000);//*********************************Turning RightValue
  }

  if (LeftValue >= 38 && RightValue >= 38) {/* Judge two values collected by the sensor. If the value collected by the left sensor is greater than or equal to 38 and the RightValue value is greater than or equal to 38, execute the following program in {} (LeftValue > = 38, indicating that there is no obstacle on the left and RightValue > = 38 that there is no obstacle on the left, so the car at this time straight */
    int value = 200; /*When the straight line has a PWM value of 200, if the value is too large, the speed of the car will be very fast, which may lead to the car can not hit the obstacle in time when it encounters the obstacle. */
    analogWrite (INPUT4_PIN, 0);
    analogWrite(INPUT3_PIN, value);//the speed value of motorA is value
    analogWrite (INPUT2_PIN, 0);
    analogWrite(INPUT1_PIN, value);//the speed value of motorB is value
    Serial.print(LeftValue);
    Serial.print("   ");
    Serial.print(RightValue);
    Serial.print("   ");
    Serial.println("go");//**********************************/ / forward
  }
}

