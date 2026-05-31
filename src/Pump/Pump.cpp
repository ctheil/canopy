#include "Pump.h"
#include "Arduino.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

Pump::Pump(int pwm_pin, int ai1_pin, int ai2_pin)
{
  pwm = pwm_pin;
  ai1 = ai1_pin;
  ai2 = ai2_pin;
}

void Pump::setup()
{
  pinMode(pwm, OUTPUT);
  pinMode(ai1, OUTPUT);
  pinMode(ai2, OUTPUT);
  this->setupTopics();
}

// TODO: use payload to toggle pump on and off
// need to figure out how the sleep cycle will work with this...
void Pump::setupTopics()
{
  log_i("[Pump::setupTopics]: E_NOT_IMPLEMENTED");
  Comms::addTopic(Comms::endpoint("/pump/on"), [this](std::string payload)
                  { 
                    auto dp = this->decodeOnPayload(payload);
                    this->on(dp.speed, dp.direction); });

  Comms::addTopic(Comms::endpoint("/pump/off"), [this](std::string payload)
                  { this->off(); });
}

OnPayload Pump::decodeOnPayload(const std::string &payload)
{
  auto def = OnPayload{255, PumpDirection::FORWARD, 1000};
  std::string data = payload;
  std::stringstream ss(data);
  std::string token;
  std::vector<std::string> split;

  while (std::getline(ss, token, ','))
  {
    split.push_back(token);
  }

  if (split.size() != 3)
    return def;

  // TODO: can throw

  int speed = std::stoi(split[0]);
  PumpDirection dir = PumpDirection::FORWARD;
  if (split[1] != "FORWARD")
    dir = PumpDirection::REVERSE;
  int duration = std::stoi(split[2]);

  return OnPayload{speed, dir, duration};
}

void Pump::dir(PumpDirection _dir)
{
  // default = forward
  int a = HIGH;
  int b = LOW;
  if (_dir == PumpDirection::REVERSE)
  {
    a = LOW;
    b = HIGH;
  }
  digitalWrite(ai1, a);
  digitalWrite(ai2, b);
}

void Pump::on(int speed, PumpDirection _dir)
{
  dir(_dir);
  int clamped = std::min(std::max(speed, 0), 255);
  analogWrite(pwm, clamped);
}
void Pump::off()
{
  analogWrite(pwm, 0);
}
