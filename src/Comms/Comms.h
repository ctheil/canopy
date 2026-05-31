#pragma once

#include "AsyncMqttClient.h"
#include <WiFi.h>
#include <string>
#include <functional>
#include "../secrets.h"

struct Topic
{
  std::string id;
  std::function<void(std::string)> handler;
  int8_t qos;
};
class Comms
{
public:
  static void setup();
  static std::string getSubscribeTopic(const std::string &plantId);
  static std::string getPublishTopic(const std::string &plantId);
  static AsyncMqttClient &mqttClient;
  static void addTopic(std::string id, std::function<void(std::string)> handler, int8_t qos = 0);
  static std::vector<Topic> &topics;

private:
  static void onMqttConnect(bool sessionPresent);
  static void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
  static void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
  static void connectToMqtt();
  static void setupMqtt();
};
