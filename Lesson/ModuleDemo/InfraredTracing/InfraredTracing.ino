#define INPUT1_PIN 6   // PWMB
#define INPUT2_PIN 10  // DIRB  ---  right
#define INPUT4_PIN 9   // PWMA
#define INPUT3_PIN 5   // DIRA  ---  left

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

void loop()
{
  int left1, centre, right1;
  left1 = digitalRead(A0);
  centre = digitalRead(A1);
  right1 = digitalRead(A2);

  if ((right1 == 1) && (centre == 0) && (left1 == 1)) //*******直行*******//
  {
    int val = 150;
    analogWrite(INPUT1_PIN, val);
    analogWrite(INPUT2_PIN, 0 ); //the speed value of motorA is val
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, val); //the speed value of motorB is val
  }

  else  if ((right1 == 0) && (centre == 1) && (left1 == 1)) //***左偏,右转***//
  {
    int val = 150;
    analogWrite(INPUT1_PIN, val); //the speed value of motorA is val
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT3_PIN, val); //the speed value of motorB is val
    analogWrite(INPUT4_PIN, 0);
  }

  else  if ((right1 == 1) && (centre == 1) && (left1 == 0)) //***右偏，左转***//
  {
    int val = 130;
    analogWrite(INPUT1_PIN, 0); //the speed value of motorA is val
    analogWrite(INPUT2_PIN, val);
    analogWrite(INPUT3_PIN, 0); //the speed value of motorB is val
    analogWrite(INPUT4_PIN, val);
  }

  if ((right1 == 0) && (centre == 0) && (left1 == 0)) //*******直行*******//
  {
    int val = 130;
    analogWrite(INPUT1_PIN, val); //the speed value of motorA is val
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, val); //the speed value of motorB is val
  }
}
