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

private:
  static constexpr char *ssid = "Brickhouse";
  static constexpr char *password = "Br1ckHous3";
  static constexpr char *server = "mqtt://192.168.0.57:1883";
};
