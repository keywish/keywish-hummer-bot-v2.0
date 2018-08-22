
#ifndef _INFRAREDAVOIDABCE_H_
#define _INFRAREDAVOIDABCE_H_
#define IA_THRESHOLD 40

/* Includes ------------------------------------------------------------------*/
#include <Arduino.h>

class InfraredAvoidance
{
  private:
    byte InfraredAvoidancePin1, InfraredAvoidancePin2;

  public:
    InfraredAvoidance(byte pin1, byte pin2);
    uint16_t GetInfraredAvoidanceLeftValue();
    uint16_t GetInfraredAvoidanceRightValue();
};
#endif
