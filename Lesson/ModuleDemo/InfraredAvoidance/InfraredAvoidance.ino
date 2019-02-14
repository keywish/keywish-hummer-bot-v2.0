#define INPUT1_PIN 6   // PWMB
#define INPUT2_PIN 10  // DIRB  ---  right
#define INPUT4_PIN 9   // PWMA
#define INPUT3_PIN 5   // DIRA  ---  left
const int leftPin = A3;
const int rightPin = A4;
float dl;
float dr;
void setup()
{
 Serial.begin(9600);
 pinMode(leftPin, INPUT);
 pinMode(rightPin, INPUT);
 delay(1000);
}

void loop()
{
  dl = analogRead(leftPin);
  dr = analogRead(rightPin);

  if (dl >= 38 && dr <= 38)
  {
   analogWrite(INPUT1_PIN,0);
   analogWrite(INPUT2_PIN, 180); //the speed value of motorA is 180
   analogWrite(INPUT3_PIN,0);
   analogWrite(INPUT4_PIN, 180); //the speed value of motorB is 180
   Serial.print(dl);
   Serial.print("   ");
   Serial.print(dr);
   Serial.print("   ");
   Serial.println("Turning left");
   delay(300);
   analogWrite(INPUT1_PIN,0);
   analogWrite(INPUT2_PIN, 0);
   analogWrite(INPUT3_PIN,0);
   analogWrite(INPUT4_PIN, 0);
   delay(1000); //********************************************//Turning left
   }

   if (dl <= 38 && dr <= 38)
   {
    analogWrite(INPUT1_PIN,0);
    analogWrite(INPUT2_PIN, 255); //the speed value of motorA is 255
    analogWrite(INPUT3_PIN,0);
    analogWrite(INPUT4_PIN, 255); //the speed value of motorB is 255
    Serial.print(dl);
    Serial.print("   ");
    Serial.print(dr);
    Serial.print("   ");
    Serial.println("Turning around");
    delay(500);
    analogWrite(INPUT1_PIN,0);
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT3_PIN,0);
    analogWrite(INPUT4_PIN, 0);
    delay(1000); //********************************************//Turning around
   }

   if (dl <= 38 && dr >= 38)
  {
   analogWrite(INPUT1_PIN,180);//the speed value of motorA is val
   analogWrite(INPUT2_PIN, 0); 
   analogWrite(INPUT3_PIN,180);//the speed value of motorA is val
   analogWrite(INPUT4_PIN, 0); 
   Serial.print(dl);
   Serial.print("   ");
   Serial.print(dr);
   Serial.print("   ");
   Serial.println("Turning right");
   delay(300);
   analogWrite(INPUT1_PIN,0);
   analogWrite(INPUT2_PIN, 0);
   analogWrite(INPUT3_PIN,0);
   analogWrite(INPUT4_PIN, 0);
   delay(1000); //********************************************//Turning right
  }

   if (dl >= 38 && dr >= 38)
  {
   analogWrite(INPUT1_PIN,180);//the speed value of motorA is val
   analogWrite(INPUT2_PIN, 0); 
   analogWrite(INPUT3_PIN,0);
   analogWrite(INPUT4_PIN, 180); //the speed value of motorB is val
   Serial.print(dl);
   Serial.print("   ");
   Serial.print(dr);
   Serial.print("   ");
   Serial.println("go");//********************************************//forward
  }
}
