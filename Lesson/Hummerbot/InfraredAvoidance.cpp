#include "InfraredAvoidance.h"

uint8_t Left, Right;

InfraredAvoidance::InfraredAvoidance(byte pin1, byte pin2)
{
  InfraredAvoidancePin1 = pin1;
  InfraredAvoidancePin2 = pin2;
  pinMode(InfraredAvoidancePin1, INPUT);
  pinMode(InfraredAvoidancePin2, INPUT);

}
uint16_t InfraredAvoidance ::GetInfraredAvoidanceLeftValue()
{
  Left = analogRead(InfraredAvoidancePin2);
  return Left;
}


uint16_t InfraredAvoidance :: GetInfraredAvoidanceRightValue()
{
  Right = analogRead(InfraredAvoidancePin1);
  return Right;
}