#pragma once

#include "ESP32MQTTClient.h"
#include <string>

class Comms
{
public:
  static void setupWifi();
  static void setupMqtt();
  static std::string getSubscribeTopic(std::string plantId);
  static std::string getPublishTopic(std::string plantId);
  static ESP32MQTTClient &mqttClient;
};
