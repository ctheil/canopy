#pragma once

#include "ESP32MQTTClient.h"
#include <string>

struct Topic
{
  std::string id;
  std::function<void(std::string)> handler;
};
class Comms
{
public:
  static void setupWifi();
  static void setupMqtt();
  static std::string getSubscribeTopic(std::string plantId);
  static std::string getPublishTopic(std::string plantId);
  static ESP32MQTTClient &mqttClient;
  static void addTopic(std::string id, std::function<void(std::string)> handler);

private:
  static std::vector<Topic> topics;
};
