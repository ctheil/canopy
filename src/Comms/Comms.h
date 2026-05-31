#pragma once

#include "AsyncMqttClient.h"
#include <WiFi.h>
#include <string>
#include <functional>
#include "../secrets.h"
#include <Ticker.h>
#include "../Prefs/Prefs.h"

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
  static AsyncMqttClient &mqttClient;
  static void addTopic(std::string id, std::function<void(std::string)> handler, int8_t qos = 0);
  static std::vector<Topic> &topics;
  static std::string endpoint(const std::string &_endpoint);

private:
  static void onMqttConnect(bool sessionPresent);
  static void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
  static void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
  static void connectToMqtt();
  static void setupMqtt();
  static void onMqttPublish(uint16_t packedId);
};
