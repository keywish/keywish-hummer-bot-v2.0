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

#define INPUT1_PIN 6   // PWMB
#define INPUT2_PIN 10  // DIRB  ---  right
#define INPUT3_PIN 5   // PWMA
#define INPUT4_PIN 9   // DIRA  ---  left
const int TrigPin = 2;  //超声波模块触发引脚
const int EchoPin = 3;  //超声波模块应答引脚
int ServoPin = 13;     //定义舵机引脚为13引脚
float da;    //定义一个变量保存超声波前方测得的距离
float dl;    //定义一个变量保存超声波左边测得的距离
float dr;    //定义一个变量保存超声波右边测得的距离

void SetServoDegree(int Angle)//舵机角度控制函数
{
   Serial.println(Angle);  //Output data to the serial port for observation
   for (int i = 0; i < 80; i++) {
    float pulsewidth = (Angle * 11) + 350;
    digitalWrite(ServoPin, HIGH);   //Set the servo interface level to high
    delayMicroseconds(pulsewidth);  //The number of microseconds of the delay pulse width value
    digitalWrite(ServoPin, LOW);    //Set the servo interface level to low
    delayMicroseconds(20000 - pulsewidth);
  }
}
void setup() {
  Serial.begin(9600);
  pinMode(ServoPin, OUTPUT);
  pinMode(INPUT1_PIN, OUTPUT); //设置电机控制引脚为输出
  pinMode(INPUT2_PIN, OUTPUT);
  pinMode(INPUT3_PIN, OUTPUT);
  pinMode(INPUT4_PIN, OUTPUT);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  SetServoDegree(90);  //设置舵机初始角度为9度，即朝正前方
  delay(1000);
}

void loop() {
  analogWrite(TrigPin, 0); //给TrigPin发送一个短脉冲，让超声波启动
  delayMicroseconds(2);
  analogWrite(TrigPin, 255);//给TrigPin发送一个10ms脉冲,开始测量障碍物距离
  delayMicroseconds(10);
  analogWrite(TrigPin, 0);
  da = pulseIn(EchoPin, HIGH) / 58.0; //超声波接收到返回的测量数据，并将该数据转化成CM
  if (da >= 50 )//----快速前进---
   
  {
    int val = 200;
    SetServoDegree(90);
    analogWrite(INPUT1_PIN, 200);
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, 200);
    Serial.print("Distance = ");
    Serial.print(da);
    Serial.print("    ");
    Serial.println("Moving advance 50");
  }
  else if ((da >= 25) && (da <= 50) )//----低速前进---
   
  {
    int val = 130;
    SetServoDegree(90);
    analogWrite(INPUT1_PIN, 130);
    analogWrite(INPUT2_PIN, 0 ); 
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, 130);
    Serial.print("Distance = ");
    Serial.print(da);
    Serial.print("    ");
    Serial.println("Moving advance30");
  }
  
  else if (da < 25)// 停止前进，测量左右两侧距离障碍物的距离
   
  {
    int val = 0;
    analogWrite(INPUT1_PIN, 0);
    analogWrite(INPUT2_PIN, val);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, val);
    Serial.print("Distance = ");
    Serial.print(da);
    Serial.print("    ");
    Serial.println("Stopped");
    delay(500);
    
    SetServoDegree(180);//-------------测量左侧距离障碍物的距离-------------------
    delay(1000);
    analogWrite(TrigPin, 0); //Send a short pulse to TrigPin
    delayMicroseconds(2);
    analogWrite(TrigPin, 255);
    delayMicroseconds(10);
    analogWrite(TrigPin, 0);
    dl = pulseIn(EchoPin, HIGH) / 58.0; //The echo time is converted to cm
    Serial.print("Left distance = ");
    Serial.print(dl);
    Serial.print("  ");
    
     SetServoDegree(20);//-----------------------测量右侧距离障碍物的距离-----------------------
    delay(1000);
    analogWrite(TrigPin, 0);
    delayMicroseconds(2);
    analogWrite(TrigPin, 255);
    delayMicroseconds(10);
    analogWrite(TrigPin, 0);
    dr = pulseIn(EchoPin, HIGH) / 58.0;
    Serial.print("Right distance = ");
    Serial.print(dr);
    Serial.print("  ");
    Serial.println();
  
    SetServoDegree(90);         //  --------超声波测完左右两侧距离，回正
    
    if ((dl >= 20) && (dl > dr))//---------------比较左右两侧距离障碍物的大小
    {
     //--------------左转------------------
      analogWrite(INPUT1_PIN, 0);
      analogWrite(INPUT2_PIN, 180);
      analogWrite(INPUT3_PIN, 0);
      analogWrite(INPUT4_PIN, 200);
      Serial.println("Turning left1");
      delay(200);
    }
    else if ((dr >= 20)&& (dr > dl))
    {
      //--------------右转------------------
      digitalWrite(INPUT1_PIN, HIGH);
      analogWrite(INPUT2_PIN, 0);
      analogWrite(INPUT3_PIN, 180);
      analogWrite(INPUT4_PIN, 0 );
      Serial.println("Turning right");
      delay(200);
    }
    else if(dr < 20 && dl < 20)
    {
      //-------------掉头------------------
      digitalWrite(INPUT1_PIN, HIGH);
      analogWrite(INPUT2_PIN, 0);
      analogWrite(INPUT3_PIN, 255);
      analogWrite(INPUT4_PIN, 0);
      Serial.println("Turning around");
      delay(700);
    }
  }
}
