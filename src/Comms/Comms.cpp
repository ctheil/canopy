#include "Comms.h"
#include "AsyncMqttClient.h"
#include <WiFi.h>
#include <string>
#include <functional>
#include "../secrets.h"
#include <Ticker.h>

AsyncMqttClient client;
AsyncMqttClient &Comms::mqttClient = client;

Ticker mqttReconnectTimer;

std::vector<Topic> _topics;
std::vector<Topic> &Comms::topics = _topics;

void Comms::setup()
{
  WiFi.begin(ssid, password);
  WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info)
               {
    if (event == ARDUINO_EVENT_WIFI_STA_GOT_IP) 
    Comms::setupMqtt();
    else if (event == ARDUINO_EVENT_WIFI_STA_DISCONNECTED) 
    mqttReconnectTimer.detach(); });
}

void Comms::setupMqtt()
{

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onMessage(onMqttMessage);

  mqttClient.setCredentials("dev_plant_sensor_001", "dev_plant_sensor_001");
  mqttClient.setServer(IPAddress(192, 168, 0, 57), 1883);

  mqttClient.setKeepAlive(15);

  mqttClient.setWill("lwt", 0, false, "I am going offline");

  Comms::connectToMqtt();
}

std::string Comms::getSubscribeTopic(const std::string &plantId)
{
  return "/esp-plant-sensor/" + plantId + "/pump";
}

std::string Comms::getPublishTopic(const std::string &plantId)
{
  return "/esp-plant-sensor/" + plantId + "/moisture";
}

void Comms::addTopic(std::string id, std::function<void(std::string)> handler, int8_t qos)
{
  topics.push_back(Topic{id, handler, qos});
}

void Comms::onMqttConnect(bool sessionPresent)
{
  log_i("Connected to MQTT.");
  for (auto &topic : topics)
  {
    Comms::mqttClient.subscribe(topic.id.c_str(), topic.qos);
  }
}

void Comms::connectToMqtt()
{
  log_i("Connecting to MQTT...");
  Comms::mqttClient.connect();
}

void Comms::onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  log_e("Disconnected from MQTT.");

  if (reason == AsyncMqttClientDisconnectReason::TLS_BAD_FINGERPRINT)
  {
    log_e("Bad server fingerprint.");
  }

  if (WiFi.isConnected())
  {
    mqttReconnectTimer.once(2, Comms::connectToMqtt);
  }
}
void Comms::onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  Topic *sub = nullptr;
  // GET TOPIC
  for (auto &s : topics)
  {
    if (s.id == topic)
    {
      sub = &s;
      break;
    }
  }
  if (!sub)
    return;

  log_i("\n[Comms::onMqttMessage]: %s heard: %s", topic, payload);
  sub->handler(std::string(payload, len));
}