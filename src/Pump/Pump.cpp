#include "Pump.h"

Pump::Pump(std::string plantId) : id{plantId}
{
  Comms *comms;
}

void Pump::setupTopics()
{
  const std::string onTopic = "/esp-plant-sensor/" + id + "/pump/on";
  comms->addTopic(onTopic, [&](std::string payload)
                  { this->on(payload); });

  const std::string offTopic = "/esp-plant-sensor/" + id + "/pump/off";
  comms->addTopic(offTopic, [&](std::string payload)
                  { this->off(payload); });
}

void Pump::on(std::string payload) {}
void Pump::off(std::string payload) {}
