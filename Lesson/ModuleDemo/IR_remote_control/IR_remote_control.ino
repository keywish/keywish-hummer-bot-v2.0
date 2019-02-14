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

#include "IR_remote.h"

#define INPUT1_PIN 6   // PWMB
#define INPUT2_PIN 10  // DIRB  ---  right
#define INPUT4_PIN 9   // PWMA
#define INPUT3_PIN 5   // DIRA  ---  left

int RECV_PIN = 12;//Define the infrared receiver pin to 12

long expedite1 = 0xFF6897;
long expedite2 = 0xFFB04F;
long advence = 0xFF18E7;
long back = 0xFF4AB5;
long stop = 0xFF38C7;
long left = 0xFF10EF;
long right = 0xFF5AA5;
static byte val = 0;
IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
	Serial.begin(9600);
	irrecv.enableIRIn(); // Initialize the infrared receiver
}

void loop() {
	if (irrecv.decode( &results)) {
		if(results.value == advence) {
			analogWrite(INPUT1_PIN, val);//the speed value of motorA is val
			analogWrite(INPUT2_PIN, 0); 
			analogWrite(INPUT3_PIN, 0);
			analogWrite(INPUT4_PIN, val); //the speed value of motorA is val
			delay(500);
			irrecv.resume(); // Receive the next value
		}
		if(results.value == expedite1) {  
      if(val == 255)
      {
        val = 255;
        } else
        val +=20;
			irrecv.resume(); // Receive the next value
		}
		if(results.value == expedite2) {
			if(val == 0)
      {
        val = 0;
        } else
        val -=20;
			irrecv.resume(); // Receive the next value
		}
		if(results.value == stop) {
			analogWrite(INPUT1_PIN, 0);
			analogWrite(INPUT2_PIN, 0); 
			analogWrite(INPUT3_PIN, 0);
			analogWrite(INPUT4_PIN, 0);
			delay(500);
			irrecv.resume(); // Receive the next value
		}
		if(results.value == left) {
			analogWrite(INPUT1_PIN, 0);
			analogWrite(INPUT2_PIN, val); //the speed value of motorA is val
			analogWrite(INPUT3_PIN, 0);
			analogWrite(INPUT4_PIN, val); //the speed value of motorA is val
			delay(500);
			analogWrite(INPUT1_PIN, 0);
			analogWrite(INPUT2_PIN, 0); //the speed value of motorA is 0
			analogWrite(INPUT3_PIN, 0);
			analogWrite(INPUT4_PIN, 0); //the speed value of motorB is 0
			irrecv.resume(); // Receive the next value
		}
		if(results.value == right) {
			analogWrite(INPUT1_PIN, val);//the speed value of motorA is val
			analogWrite(INPUT2_PIN, 0); 
			analogWrite(INPUT3_PIN, val);//the speed value of motorA is val
			analogWrite(INPUT4_PIN, 0); 
			delay(500);
			analogWrite(INPUT1_PIN, 0);
			analogWrite(INPUT2_PIN, 0); //the speed value of motorA is 0
			analogWrite(INPUT3_PIN, 0);
			analogWrite(INPUT4_PIN, 0); //the speed value of motorB is 0
			irrecv.resume(); // Receive the next value
		}
		if(results.value == back) {
			analogWrite(INPUT1_PIN, 0);
			analogWrite(INPUT2_PIN, val); //the speed value of motorA is val
			analogWrite(INPUT3_PIN, val); //the speed value of motorA is val
			analogWrite(INPUT4_PIN, 0);
			delay(500);
			irrecv.resume(); // Receive the next value
		}
		Serial.println(results.value, HEX);//The hexadecimal line feed output code
		Serial.println();//For the convenience of viewing the output, add a blank line
		irrecv.resume(); // Receive the next value
	}
}
