#pragma once

#include "../Comms/Comms.h"

class Pump
{
public:
  Pump(const std::string &plantId);
  void on(const std::string &payload);
  void off(const std::string &payload);

private:
  void setupTopics();
  std::string id;
};