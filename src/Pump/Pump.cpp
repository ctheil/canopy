#include "Pump.h"
#include "Arduino.h"
#include <algorithm>

Pump::Pump(const int &pwa_pin, const int &ai1_pin, const int &ai2_pin)
{
  pwa = pwa_pin;
  ai1 = ai1_pin;
  ai2 = ai2_pin;

  this->setupTopics();
}

void Pump::setup()
{
  pinMode(pwa, OUTPUT);
  pinMode(ai1, OUTPUT);
  pinMode(ai2, OUTPUT);
}

// TODO: use payload to toggle pump on and off
// need to figure out how the sleep cycle will work with this...
void Pump::setupTopics()
{
  log_i("[Pump::setupTopics]: E_NOT_IMPLEMENTED");
  // const std::string onTopic = "/esp-plant-sensor/" + this->id + "/pump/on";
  // Comms::addTopic(onTopic, [this](std::string payload)
  //                 { this->on(); });

  // const std::string offTopic = "/esp-plant-sensor/" + this->id + "/pump/off";
  // Comms::addTopic(offTopic, [this](std::string payload)
  //                 { this->off(); });
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

void Pump::on(int speed, Pump::PumpDirection dir = Pump::PumpDirection::FORWARD)
{
  int clamped = std::min(std::max(speed, 0), 255);
  analogWrite(pwa, clamped);
}
void Pump::off()
{
  analogWrite(pwa, 0);
}
