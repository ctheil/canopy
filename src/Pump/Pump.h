#pragma once

#include "../Comms/Comms.h"
#include <string>
#include <sstream>
#include <vector>

// PUMP with 4 5gph leads takes ~30mins to pump 1gal

enum PumpDirection
{
  FORWARD,
  REVERSE
};

struct OnPayload
{
  int speed;
  PumpDirection direction;
  int durationMs;
};

class Pump
{
public:
  Pump(int pwm_pin, int ai1_pin, int ai2_pin);
  void on(int speed = 255, PumpDirection dir = PumpDirection::FORWARD);
  void off();
  void setup();

private:
  void setupTopics();
  int pwm;
  int ai1;
  int ai2;
  void dir(PumpDirection _dir);
  OnPayload decodeOnPayload(const std::string &payload);
};