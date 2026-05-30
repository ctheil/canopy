#include "Pump.h"
#include "Arduino.h"
#include <algorithm>

Pump::Pump(const int &pwm_pin, const int &ai1_pin, const int &ai2_pin)
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
  const std::string onTopic = "/canopy/did002/pump/on";
  Comms::addTopic(onTopic, [this](std::string payload)
                  { this->on(255, Pump::PumpDirection::FORWARD); });

  const std::string offTopic = "/canopy/did002/pump/off";
  Comms::addTopic(offTopic, [this](std::string payload)
                  { this->off(); });
}

void Pump::dir(Pump::PumpDirection _dir)
{
  // default = forward
  int a = HIGH;
  int b = LOW;
  if (_dir == Pump::PumpDirection::REVERSE)
  {
    a = LOW;
    b = HIGH;
  }
  digitalWrite(ai1, a);
  digitalWrite(ai2, b);
}

void Pump::on(int speed = 255, Pump::PumpDirection _dir = Pump::PumpDirection::FORWARD)
{
  dir(_dir);
  int clamped = std::min(std::max(speed, 0), 255);
  analogWrite(pwm, clamped);
}
void Pump::off()
{
  analogWrite(pwm, 0);
}
