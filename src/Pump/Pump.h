#pragma once

#include "../Comms/Comms.h"
#include <string>
#include <sstream>
#include <vector>

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
  Pump(const int &pwm_pin, const int &ai1_pin, const int &ai2_pin);
  void on(int speed, PumpDirection dir);
  void off();
  void setup();

  void dir(PumpDirection _dir);

private:
  void setupTopics();
  int pwm;
  int ai1;
  int ai2;
  OnPayload decodeOnPayload(const std::string &payload);
};