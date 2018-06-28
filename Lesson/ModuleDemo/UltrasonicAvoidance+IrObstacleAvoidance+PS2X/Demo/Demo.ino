#include "PS2X_lib.h" //for v1.6

int E1 = 5; //PWMA
int M1 = 9; //DIRA****************************************left
int E2 = 6; //PWMB 
int M2 = 10; //DIRB****************************************right

PS2X ps2x; 

int error = 0;
byte type = 0;
byte vibrate = 0;
int vb;
int KK;
int banduan = 0;

int TrigPin = 2; 
int EchoPin = 3;
int distance;

const int leftPin = A3; 
const int rightPin = A4; 
float dl;
float dr; 

void setup() {
	Serial.begin(9600);
	pinMode(TrigPin, OUTPUT);
	pinMode(EchoPin, INPUT); 
	pinMode(leftPin, INPUT); 
	pinMode(rightPin, INPUT);
	error = ps2x.config_gamepad(11, 7, 8, 4, true, true);

	digitalWrite(M1, 0); 
	analogWrite(E1, 0); 
	digitalWrite(M2, 0);
	analogWrite(E2, 0); 
}

void loop() {
	ps2x.read_gamepad(false, vibrate); 

	if ( ps2x.Button( PSB_R1)) {// print stick values if either is TRUE
		vb = ps2x.Analog(PSS_RX); 
		Serial.println(vb);
		if ( vb < 5) {//From left to right 0~255, from top to bottom 0~255 
			banduan = 1; 
			turnLeft(); 
			Serial.println("left"); 
		} 
		if ( vb > 250) { 
			banduan = 1;
			turnRight(); 
			Serial.println("right");
		} 
		else {
			goStop();
		}
	}

	if ( ps2x.Button(PSB_R1)) {// print stick values if either is TRUE
		KK = ps2x.Analog(PSS_RY); 
		Serial.println(KK);
		if ( KK < 5) {
			banduan = 1;
			forward();
			Serial.println("GO");
		} 

		if ( KK > 250) { 
			banduan = 1;
			back(); 
			Serial.println("back");  
		}
	}

	else {
		goStop();
	}
	delay(50);

	dl = analogRead(leftPin); 
	dr = analogRead(rightPin);

	if (dl >= 38 && dr <= 38) { 
		analogWrite(M1, 0); 
		analogWrite(E1, 180); //the speed value of motorA is 180 
		analogWrite(M2, 180);//the speed value of motorB is 180
		analogWrite(E2, 0); 
		delay(100);
		goStop();
	}//********************************************//left

	if (dl <= 38 && dr <= 38) {
		analogWrite(M1, 255); //the speed value of motorA is 255 
		analogWrite(E1, 0); 
		analogWrite(M2, 0);
		analogWrite(E2, 255); //the speed value of motorB is 255
		Serial.print(dl);
		delay(500);
		goStop();//********************************************///Turning around
	}

	if (dl <= 38 && dr >= 38) {
		analogWrite(M1, 180); //the speed value of motorA is 180 
		analogWrite(E1, 0); 
		analogWrite(M2, 0);
		analogWrite(E2, 180); //the speed value of motorA is 180
		delay(100);
		goStop();
		//********************************************//right
	}
}

void forward() {
	digitalWrite(TrigPin, LOW); // Makes send out ultrasonic signal interface low2μs
	delayMicroseconds(2);
	digitalWrite(TrigPin, HIGH); // Makes sending the ultrasonic signal interface high 10μs, here is at least 10μs
	delayMicroseconds(10);
	digitalWrite(TrigPin, LOW); // Keep emitting ultrasonic signal interface low
	int distance = pulseIn(EchoPin, HIGH); // Read pulse time
	distance = distance / 58; // Convert pulse time to distance (unit: cm)
	// delay(50); 
	if ( distance >= 20) {
		analogWrite(M1, 0); 
		analogWrite(E1, 180); //the speed value of motorA is 180 
		analogWrite(M2, 0);
		analogWrite(E2, 180); //the speed value of motorA is 180
	}
	else {
		goStop();
	}
}
void back() {
	int val = 180;
	analogWrite(E1, 0); 
	analogWrite(M1, val); //the speed value of motorA is val  
	analogWrite(E2, 0);
	analogWrite(M2, val); //the speed value of motorB is val
}
void turnLeft() { 
	int val = 180;
	analogWrite(M1, 0); 
	analogWrite(E1, val); //the speed value of motorA is val 
	analogWrite(E2, 0);
	analogWrite(M2, val); //the speed value of motorB is val 
	delay(100);
	goStop();
}

void turnRight() {
	int val = 180;
	analogWrite(E1, 0); 
	analogWrite(M1, val); //the speed value of motorA is val 
	analogWrite(M2, 0);
	analogWrite(E2, val); //the speed value of motorB is val;
	delay(100);
	goStop();
}

void goStop() { 
	int val = 0;
	analogWrite(M1, 0); 
	analogWrite(E1, val); //the speed value of motorA is val 
	analogWrite(M2, 0);
	analogWrite(E2, val); //the speed value of motorB is val
} 
