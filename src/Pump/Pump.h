#pragma once

#include "../Comms/Comms.h"

class Pump
{
public:
  Pump(const int &pwa_pin, const int &ai1_pin, const int &ai2_pin);
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
  std::string id;
  int pwa;
  int ai1;
  int ai2;
};