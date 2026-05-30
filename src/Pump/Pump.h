#pragma once

#include "../Comms/Comms.h"

class Pump
{
public:
  Pump(const std::string &plantId);
  void on(std::string payload);
  void off(std::string payload);

private:
  void setupTopics();
  std::string id;
  Comms *comms;
};