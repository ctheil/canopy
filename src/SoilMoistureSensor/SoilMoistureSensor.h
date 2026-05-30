#pragma once

#include "Arduino.h"
#include "../Comms/Comms.h"
#include <string>

class SoilMoistureSensor
{
public:
  SoilMoistureSensor(int sensorPin, const std::string &plantId);
  int getMoisturePercentage();
  void publish(char *buffer);

private:
  int pin;
  static int constexpr waterValue = 1150;
  static int constexpr airValue = 2500;
  std::string id;
};
