const int leftPin = A3;
const int rightPin = A4;
int dl;
int dr;
void setup() {
	Serial.begin(9600);
	pinMode(leftPin, INPUT);
	pinMode(rightPin, INPUT);
	delay(1000);
}
void loop() {
	dl = analogRead(leftPin);
	dr = analogRead(rightPin);
	Serial.print("left:");
	Serial.print(dl);
	Serial.print("   ");
	Serial.print("right:");
	Serial.println(dr);
}