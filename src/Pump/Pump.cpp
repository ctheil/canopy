#include "Pump.h"

Pump::Pump(const std::string &plantId) : id{plantId}
{
  this->setupTopics();
}

void Pump::setupTopics()
{
  const std::string onTopic = "/esp-plant-sensor/" + this->id + "/pump/on";
  Comms::addTopic(onTopic, [this](std::string payload)
                  { this->on(payload); });

  const std::string offTopic = "/esp-plant-sensor/" + this->id + "/pump/off";
  Comms::addTopic(offTopic, [this](std::string payload)
                  { this->off(payload); });
}

void Pump::on(const std::string &payload) {}
void Pump::off(const std::string &payload) {}
