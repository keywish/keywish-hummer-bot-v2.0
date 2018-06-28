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
 *
 * [Title]
 * [Diagram]

 */
#include "Servo.h" 
  
Servo myservo;  // Create a servo motor object
  
char inByte = 0; //Serial port to receive data
int angle = 0;  //Angle value 
String temp = "";//Temporary character variables, or use it for the cache
  
void setup()   
{  
  myservo.attach(13);    //Define the steering gear pin to 13
  Serial.begin(9600);  //Set the baud rate
}  
  
  
void loop()   
{  
  while (Serial.available() > 0) //Determine whether the serial data
  {  
    inByte = Serial.read();//Read data, the serial port can only read 1 character
    temp += inByte;//The characters read into temporary variables inside the cache, 
                   //Continue to determine the serial port there is no data, know all the data read out  
   }  
  
   if(temp != "")   //Determine whether the temporary variable is empty
   {  
    angle = temp.toInt();    //Convert variable string type to integer  
    Serial.println(angle);  //Output data to the serial port for observation
   }  
  temp = "";//Please see temporary variables  
  myservo.write(angle);  //Control the servo to rotate the corresponding angle.  
  delay(100);//Delayed 100 milliseconds 
}  
