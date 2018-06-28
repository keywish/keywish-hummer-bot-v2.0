int E1 = 5; //PWMA
int M1 = 9; //PWMA
int E2 = 6; //PWMB
int M2 = 10; //PWMB
void setup() {
    Serial.begin(9600);
    pinMode(E1, OUTPUT);
    digitalWrite(E1, LOW); // When not sending PWM, we want it low
    pinMode(M1, OUTPUT);
    digitalWrite(M1, LOW); // When not sending PWM, we want it low
    pinMode(E2, OUTPUT);
    digitalWrite(E2, LOW); // When not sending PWM, we want it low
    pinMode(M2, OUTPUT);
    digitalWrite(M2, LOW); // When not sending PWM, we want it low
}

void loop() {
	analogWrite(M1, 0);
	analogWrite(E1, 150); //the speed value of motorA is 150
	analogWrite(M2, 0);
	analogWrite(E2, 150); //the speed value of motorB is 150
	delay(5000);
	//******** ******************************//forward
	analogWrite(M1, 0);
	analogWrite(E1, 0); //the speed value of motorA is 0
analogWrite(M2, 0);
	analogWrite(E2, 0); //the speed value of motorB is 0
	delay(1000);//********************************************//stop
	analogWrite(M1, 150);//the speed value of motorA is 150
	analogWrite(E1, 0);
	analogWrite(M2, 150);//the speed value of motorA is 150
	analogWrite(E2, 0);
	delay(5000);//*********************************************//back
	analogWrite(M1, 0);
	analogWrite(E1, 0); //the speed value of motorA is 0
	analogWrite(M2, 0);
	analogWrite(E2, 0); //the speed value of motorB is 0
	delay(1000);
	//******* ***************************************//stop
	analogWrite(M1, 0);
	analogWrite(E1, 180); //the speed value of motorA is 180
	analogWrite(M2, 180);//the speed value of motorB is 180
	analogWrite(E2, 0);
	delay(3000);
	//*******************************************//left
	analogWrite(M1, 0);
	analogWrite(E1, 0); //the speed value of motorA is 0
	analogWrite(M2, 0);
	analogWrite(E2, 0); //the speed value of motorB is 0
	delay(1000); //*******************************************//stop
	analogWrite (M1, 200); //the speed value of motorA is 200
	analogWrite(E1, 0);
	analogWrite (M2, 0);
	analogWrite(E2, 200); //the speed value of motorB is 200
	delay(3000);//*** ***************************************//right
}