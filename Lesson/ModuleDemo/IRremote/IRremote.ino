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

#include "IRremote.h"
int E1 = 5; //PWMA
int M1 = 9; //DIRA****************************************left
int E2 = 6; //PWMB
int M2 = 10; //DIRB****************************************right

int RECV_PIN = 12;//Define the infrared receiver pin to 12

long expedite1 = 0xFF6897;
long expedite2 = 0xFFB04F;
long advence = 0xFF18E7;
long back = 0xFF4AB5;
long stop = 0xFF38C7;
long left = 0xFF10EF;
long right = 0xFF5AA5;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
	Serial.begin(9600);
	irrecv.enableIRIn(); // Initialize the infrared receiver
}

void loop() {
	if (irrecv.decode( &results)) {
		if(results.value == advence) {
			int val = 150;
			analogWrite(M1, 0);
			analogWrite(E1, val); //the speed value of motorA is val
			analogWrite(M2, 0);
			analogWrite(E2, val); //the speed value of motorA is val
			delay(500);
			irrecv.resume(); // Receive the next value
		}
		if(results.value == expedite1) {
			int val = 200;
			analogWrite(M1, 0);
			analogWrite(E1, val);//the speed value of motorA is val
			analogWrite(M2, 0);
			analogWrite(E2, val); //the speed value of motorA is val
			delay(500);
			irrecv.resume(); // Receive the next value
		}
		if(results.value == expedite2) {
			int val = 255;
			analogWrite(M1, 0);
			analogWrite(E1, val); //the speed value of motorA is val
			analogWrite(M2, 0);
			analogWrite(E2, val); //the speed value of motorA is val
			delay(500);
			irrecv.resume(); // Receive the next value
		}

		if(results.value == stop) {
			int val = 0;
			analogWrite(M1, 0);
			analogWrite(E1, val); //the speed value of motorA is val
			analogWrite(M2, 0);
			analogWrite(E2, val);//the speed value of motorA is val
			delay(500);
			irrecv.resume(); // Receive the next value
		}
		if(results.value == left) {
			int val = 150;
			analogWrite(M1, 0);
			analogWrite(E1, val); //the speed value of motorA is val
			analogWrite(E2, 0);
			analogWrite(M2, val); //the speed value of motorA is val
			delay(500);
			analogWrite(M1, 0);
			analogWrite(E1, 0); //the speed value of motorA is 0
			analogWrite(M2, 0);
			analogWrite(E2, 0); //the speed value of motorB is 0
			irrecv.resume(); // Receive the next value
		}
		if(results.value == right) {
			int val = 150;
			analogWrite(E1, 0);
			analogWrite(M1, val); //the speed value of motorA is val
			analogWrite(M2, 0);
			analogWrite(E2, val); //the speed value of motorA is val
			delay(500);
			analogWrite(M1, 0);
			analogWrite(E1, 0); //the speed value of motorA is 0
			analogWrite(M2, 0);
			analogWrite(E2, 0); //the speed value of motorB is 0
			irrecv.resume(); // Receive the next value
		}
		if(results.value == back) {
			int val = 150;
			analogWrite(E1, 0);
			analogWrite(M1, val); //the speed value of motorA is val
			analogWrite(E2, 0);
			analogWrite(M2, val); //the speed value of motorA is val
			delay(500);
			irrecv.resume(); // Receive the next value
		}
		Serial.println(results.value, HEX);//The hexadecimal line feed output code
		Serial.println();//For the convenience of viewing the output, add a blank line
		irrecv.resume(); // Receive the next value
	}
}

