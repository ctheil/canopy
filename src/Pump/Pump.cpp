#include "Pump.h"

Pump::Pump(std::string plantId) : id{plantId}
{
}

void Pump::setupTopics()
{
  const std::string onTopic = "/esp-plant-sensor/" + id + "/pump/on";
  Comms::addTopic(onTopic, [&](std::string payload)
                  { this->on(payload); });

  const std::string offTopic = "/esp-plant-sensor/" + id + "/pump/off";
  Comms::addTopic(offTopic, [&](std::string payload)
                  { this->off(payload); });
}

void Pump::on(std::string payload) {}
void Pump::off(std::string payload) {}
