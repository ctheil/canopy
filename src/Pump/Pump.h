#pragma once

#include "../Comms/Comms.h"

class Pump
{
public:
  Pump(const int &pwm_pin, const int &ai1_pin, const int &ai2_pin);
  enum PumpDirection
  {
    FORWARD,
    REVERSE
  };
  void on(int speed, Pump::PumpDirection dir);
  void off();
  void setup();

  void dir(Pump::PumpDirection _dir);

private:
  void setupTopics();
  int pwm;
  int ai1;
  int ai2;
};