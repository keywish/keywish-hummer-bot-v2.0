#define HB_INPUT1_PIN 6
#define HB_INPUT2_PIN 10
#define HB_INPUT3_PIN 9
#define HB_INPUT4_PIN 5

void setup() {
  Serial.begin(9600);
  pinMode(HB_INPUT1_PIN, OUTPUT);
  digitalWrite(HB_INPUT1_PIN, LOW); // When not sending PWM, we want it low
  pinMode(HB_INPUT2_PIN, OUTPUT);
  digitalWrite(HB_INPUT2_PIN, LOW); // When not sending PWM, we want it low
  pinMode(HB_INPUT3_PIN, OUTPUT);
  digitalWrite(HB_INPUT3_PIN, LOW); // When not sending PWM, we want it low
  pinMode(HB_INPUT4_PIN, OUTPUT);
  digitalWrite(HB_INPUT4_PIN, LOW); // When not sending PWM, we want it low
}

void loop() {
  analogWrite(HB_INPUT1_PIN, 200);
  analogWrite(HB_INPUT2_PIN, LOW);
  analogWrite(HB_INPUT3_PIN, LOW);
  analogWrite(HB_INPUT4_PIN, 200);
  delay(5000);
  //******** ******************************//forward
  analogWrite(HB_INPUT1_PIN, LOW);
  analogWrite(HB_INPUT2_PIN, LOW);
  analogWrite(HB_INPUT3_PIN, LOW);
  analogWrite(HB_INPUT4_PIN, LOW);
  delay(1000);//********************************************//stop
  analogWrite(HB_INPUT1_PIN, LOW);
  analogWrite(HB_INPUT2_PIN, 200);
  analogWrite(HB_INPUT3_PIN, 200);
  analogWrite(HB_INPUT4_PIN, LOW);
  delay(5000);//*********************************************//back
  analogWrite(HB_INPUT1_PIN, LOW);
  analogWrite(HB_INPUT2_PIN, LOW);
  analogWrite(HB_INPUT3_PIN, LOW);
  analogWrite(HB_INPUT4_PIN, LOW);
  delay(1000);
  //******* ***************************************//stop
  analogWrite(HB_INPUT1_PIN, LOW);
  analogWrite(HB_INPUT2_PIN, 200);
  analogWrite(HB_INPUT3_PIN, LOW);
  analogWrite(HB_INPUT4_PIN, 200);
  delay(3000);
  //*******************************************//left
  analogWrite(HB_INPUT1_PIN, LOW);
  analogWrite(HB_INPUT2_PIN, LOW);
  analogWrite(HB_INPUT3_PIN, LOW);
  analogWrite(HB_INPUT4_PIN, LOW);
  delay(1000); //*******************************************//stop
  analogWrite(HB_INPUT1_PIN, 200);
  analogWrite(HB_INPUT2_PIN, LOW);
  analogWrite(HB_INPUT3_PIN, 200);
  analogWrite(HB_INPUT4_PIN, LOW);
  delay(3000);//*** ***************************************//right
}
