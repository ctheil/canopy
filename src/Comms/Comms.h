#pragma once

#include "ESP32MQTTClient.h"
#include <WiFi.h>
#include <string>
#include <functional>
#include "../secrets.h"

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
  static std::string getSubscribeTopic(const std::string &plantId);
  static std::string getPublishTopic(const std::string &plantId);
  static ESP32MQTTClient &mqttClient;
  static void addTopic(std::string id, std::function<void(std::string)> handler);
  static std::vector<Topic> &topics;
};
