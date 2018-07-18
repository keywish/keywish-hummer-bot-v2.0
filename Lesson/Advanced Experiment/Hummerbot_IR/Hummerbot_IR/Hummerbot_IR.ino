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
#include "IRremote.h"/*In this section, we use infrared remote control, so we need to call the corresponding library file, as for what is in the library file, we will not study, and interested friends can drive research. We have put this library files on the CD-ROM, we need to copy this folder to the Arduino IDE installation path "libraries" folder, otherwise the program can not compile. */
int INPUT3_PIN = 5;//PWMA
int INPUT4_PIN = 9;//DIRA****************************************left
int INPUT1_PIN = 6;//PWMB
int INPUT2_PIN = 10;//DIRB****************************************right
int RECV_PIN = 12;
long expedite1 = 22;
long expedite2 = 13;
byte advance = 24;
byte back = 82;
byte stop = 28;
byte left = 8;
byte right = 90;
IRremote *mIrRecv;
void setup() {
  Serial.begin(9600);
  Serial.println("Get last update from https://github.com/keywish/keywish-beetle-bot");
  pinMode(INPUT1_PIN, OUTPUT);
  pinMode(INPUT3_PIN, OUTPUT);
  pinMode(INPUT4_PIN, OUTPUT);
  pinMode(INPUT2_PIN, OUTPUT);
  mIrRecv = new IRremote(RECV_PIN);
  mIrRecv->begin();// Initialize the infrared receiver
}
void loop() {
  byte irKeyCode;
  if (irKeyCode = mIrRecv->getCode()) {/* Read the valueue received by the infrared */
    if (irKeyCode == advance) { /* Judgment on the received valueue, if this valueue is advence, execute the following {} command, here is the forward instruction. */
      int value = 150;
      analogWrite (INPUT4_PIN, 0);
      analogWrite(INPUT3_PIN, value);//the speed valueue of motorA is value
      analogWrite (INPUT2_PIN, 0);
      analogWrite(INPUT1_PIN, value);//the speed valueue of motorB is value
      delay(500);  // Receive the next valueue
      analogWrite(INPUT3_PIN, 0);
      analogWrite(INPUT4_PIN, 0);//the speed valueue of motorA is 0
      analogWrite(INPUT1_PIN, 0);
      analogWrite(INPUT2_PIN, 0);//the speed valueue of motorB is 0
    }
    if (irKeyCode == expedite1) {/*Judgment on the valueue received, if this valueue is expedite1,execute the command in{}below, here is the acceleration 1 command.*/
      int value = 200;
      analogWrite (INPUT4_PIN, 0);
      analogWrite(INPUT3_PIN, value);//the speed valueue of motorA is value
      analogWrite (INPUT2_PIN, 0);
      analogWrite(INPUT1_PIN, value);//the speed valueue of motorB is value
      delay(500);
      analogWrite(INPUT3_PIN, 0);
      analogWrite(INPUT4_PIN, 0);//the speed valueue of motorA is 0
      analogWrite(INPUT1_PIN, 0);
      analogWrite(INPUT2_PIN, 0);//the speed valueue of motorB is 0
    }
    if (irKeyCode == expedite2) {/*Judgment on the received valueue, if the valueue is expedite2,execute the command {} below,here for the acceleration 2 command. */
      int value = 255;
      analogWrite(INPUT4_PIN, 0);
      analogWrite(INPUT3_PIN, value);//the speed valueue of motorA is value
      analogWrite(INPUT2_PIN, 0);
      analogWrite(INPUT1_PIN, value);//the speed valueue of motorB is value
      delay(500);
      analogWrite(INPUT3_PIN, 0);
      analogWrite(INPUT4_PIN, 0);//the speed valueue of motorA is 0
      analogWrite(INPUT1_PIN, 0);
      analogWrite(INPUT2_PIN, 0);//the speed valueue of motorB is 0
    }
    if (irKeyCode == stop) { /* To judge the valueue received, if this valueue is stop, execute the command in the following {}, here is the stop instruction. */
      int value = 0;
      analogWrite(INPUT4_PIN, 0);
      analogWrite(INPUT3_PIN, value);//the speed valueue of motorA is value
      analogWrite(INPUT2_PIN, 0);
      analogWrite(INPUT1_PIN, value);//the speed valueue of motorB is value
    }
    if (irKeyCode == left) {/* Judgment on the received valueue, if the valueue is left, execute the command in the following {}, here is the instruction to the left. */
      int value = 150;
      analogWrite(INPUT4_PIN, 0);
      analogWrite(INPUT3_PIN, 0);//the speed valueue of motorA is value
      analogWrite(INPUT1_PIN, value);
      analogWrite(INPUT2_PIN, 0);//the speed valueue of motorB is value
      delay(500);/* Rotate 500ms to the left and stop, otherwise the car will always be spinning around. */
      analogWrite(INPUT4_PIN, 0);
      analogWrite(INPUT3_PIN, 0);//the speed valueue of motorA is 0
      analogWrite(INPUT2_PIN , 0);
      analogWrite(INPUT1_PIN, 0);//the speed valueue of motorB is 0
    }
    if (irKeyCode == right) {/* Judgment on the received valueue, if the valueue is right, execute the command in the following {}, here is the command to the right. */
      int value = 150;
      analogWrite(INPUT3_PIN, value);
      analogWrite(INPUT4_PIN, 0);//the speed valueue of motorA is value
      analogWrite(INPUT2_PIN, 0);
      analogWrite(INPUT1_PIN, 0);//the speed valueue of motorA is value
      delay(500);
      analogWrite(INPUT3_PIN, 0);
      analogWrite(INPUT4_PIN, 0);//the speed valueue of motorA is 0
      analogWrite(INPUT1_PIN, 0);
      analogWrite(INPUT2_PIN, 0);//the speed valueue of motorB is 0
    }
    if (irKeyCode == back) {/* Judgment on the received valueue, if the valueue is back, execute the command {} below, here for the back instruction. */
      int value = 150;
      analogWrite(INPUT3_PIN, 0);
      analogWrite(INPUT4_PIN, value);//the speed valueue of motorA is value
      analogWrite(INPUT1_PIN, 0);
      analogWrite(INPUT2_PIN, value);//the speed valueue of motorA is value
      delay(500);
      analogWrite(INPUT3_PIN, 0);
      analogWrite(INPUT4_PIN, 0);//the speed valueue of motorA is 0
      analogWrite(INPUT1_PIN, 0);
      analogWrite(INPUT2_PIN, 0);//the speed valueue of motorB is 0
    }
    Serial.println(irKeyCode, HEX);// Output the receive code in hexadecimal
    Serial.println();// Add a blank line for easy viewing of the output
  }
}

