int E1 = 5; //PWMA
int M1 = 9; //DIRA****************************************left
int E2 = 6; //PWMB
int M2 = 10; //DIRB****************************************right

void setup() {
	Serial.begin(9600);
}

void loop() {
	int left1, centre, right1;
	left1 = analogRead(A0);
	centre = analogRead(A1);
	right1 = analogRead(A2);

	if ((right1 >= 975) && (centre <= 8) && (left1 >= 975)) {//*******straight*******//
		int val = 150;
		analogWrite(M1, 0);
		analogWrite(E1, val); //the speed value of motorA is val
		analogWrite(M2, 0);
		analogWrite(E2, val); //the speed value of motorB is val
	}

	else if ((right1 <= 8) && (centre >= 975) && (left1 >= 975)) {//***Left bias,Turn right***//
		int val = 150;
		analogWrite(E1, 0);
		analogWrite(M1, val); //the speed value of motorA is val
		analogWrite(M2, 0);
		analogWrite(E2, val); //the speed value of motorB is val
	}

	else if ((right1 >= 975) && (centre >= 975) && (left1 <= 8)) {//***Turn bias，Left right***//
		int val = 130;
		analogWrite(M1, 0);
		analogWrite(E1, val); //the speed value of motorA is val
		analogWrite(E2, 0);
		analogWrite(M2, val); //the speed value of motorB is val
	}

	if ((right1 <= 8) && (centre <= 8) && (left1 <= 8)) {//*******straight*******//
		int val = 130;
		analogWrite(M1, 0);
		analogWrite(E1, val); //the speed value of motorA is val
		analogWrite(M2, 0);
		analogWrite(E2, val); //the speed value of motorB is val
	}
}
