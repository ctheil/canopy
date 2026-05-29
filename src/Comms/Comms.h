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
  static constexpr char *ssid = "Brickhouse";
  static constexpr char *password = "Br1ckHous3";
  static constexpr char *server = "mqtt://192.168.0.57:1883";
  static std::vector<Topic> topics;
};
