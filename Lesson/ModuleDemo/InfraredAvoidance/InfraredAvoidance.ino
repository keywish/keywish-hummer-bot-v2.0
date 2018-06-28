int E1 = 5; //PWMA
int M1 = 9; //DIRA****************************************left
int E2 = 6; //PWMB
int M2 = 10; //DIRB****************************************right
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
   analogWrite(M1,0);
   analogWrite(E1, 180); //the speed value of motorA is 180
   analogWrite(M2,180);
   analogWrite(E2, 0); //the speed value of motorB is 180
   Serial.print(dl);
   Serial.print("   ");
   Serial.print(dr);
   Serial.print("   ");
   Serial.println("Turning left");
   delay(300);
   analogWrite(M1,0);
   analogWrite(E1, 0);
   analogWrite(M2,0);
   analogWrite(E2, 0);
   delay(1000); //********************************************//Turning left
   }

   if (dl <= 38 && dr <= 38)
   {
    analogWrite(M1,255);
    analogWrite(E1, 0); //the speed value of motorA is 255
    analogWrite(M2,0);
    analogWrite(E2, 255); //the speed value of motorB is 255
    Serial.print(dl);
    Serial.print("   ");
    Serial.print(dr);
    Serial.print("   ");
    Serial.println("Turning around");
    delay(500);
    analogWrite(M1,0);
    analogWrite(E1, 0);
    analogWrite(M2,0);
    analogWrite(E2, 0);
    delay(1000); //********************************************//Turning around
   }

   if (dl <= 38 && dr >= 38)
  {
   analogWrite(M1,180);
   analogWrite(E1, 0); //the speed value of motorA is val
   analogWrite(M2,0);
   analogWrite(E2, 180); //the speed value of motorA is val
   Serial.print(dl);
   Serial.print("   ");
   Serial.print(dr);
   Serial.print("   ");
   Serial.println("Turning right");
   delay(300);
   analogWrite(M1,0);
   analogWrite(E1, 0);
   analogWrite(M2,0);
   analogWrite(E2, 0);
   delay(1000); //********************************************//Turning right
  }

   if (dl >= 38 && dr >= 38)
  {
   int val=180;
   analogWrite(M1,0);
   analogWrite(E1, val); //the speed value of motorA is val
   analogWrite(M2,0);
   analogWrite(E2, val); //the speed value of motorB is val
   Serial.print(dl);
   Serial.print("   ");
   Serial.print(dr);
   Serial.print("   ");
   Serial.println("go");//********************************************//forward
  }
}
