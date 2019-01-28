<<<<<<< HEAD

=======
>>>>>>> 1e4a15db1ab979ff5589c0725b45aaac1a394517
void setup() {
	Serial.begin(9600);
        pinMode(A0,INPUT);
        pinMode(A1,INPUT);
        pinMode(A2,INPUT);        
}
void loop() {
	int left, centre, right;
	left = analogRead(A0);
	centre = analogRead(A1);
	right = analogRead(A2);
<<<<<<< HEAD

        Serial.print("left:");
	Serial.print(left);
	Serial.println("   ");
        
	Serial.print("centre:");
	Serial.print(centre);
	Serial.print("   ");

        Serial.print("right:");
	Serial.print(right);
	Serial.print("   ");	

}
=======
	Serial.print("right:");
	Serial.print(right);
	Serial.print("   ");
	Serial.print("centre:");
	Serial.print(centre);
	Serial.print("   ");
	Serial.print("left:");
	Serial.print(left);
	Serial.println("   ");
}
>>>>>>> 1e4a15db1ab979ff5589c0725b45aaac1a394517
