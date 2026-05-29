#include "Comms.h"
#include "ESP32MQTTClient.h"
#include <WiFi.h>
#include <string>
#include <functional>

ESP32MQTTClient client;
ESP32MQTTClient &Comms::mqttClient = client;
std::vector<Topic> topics;

void Comms::setupWifi()
{
  WiFi.begin(ssid, password);
  WiFi.setHostname("c3Test");
}

void Comms::setupMqtt()
{

  mqttClient.enableDebuggingMessages();

  mqttClient.setURI(server, "dev_plant_sensor_001", "dev_plant_sensor_001");
  mqttClient.setMqttClientName("ESP32_Client_dev_plant_sensor");

  mqttClient.enableLastWillMessage("lwt", "I am going offline");
  mqttClient.setKeepAlive(30);
  mqttClient.setOnMessageCallback(
      [](const std::string &topic, const std::string &payload)
      {
        log_i("Global callback %s: %s", topic.c_str(), payload.c_str());
      });

  mqttClient.loopStart(); // Non-blocking!
}

std::string Comms::getSubscribeTopic(std::string plantId)
{
  return "/esp-plant-sensor/" + plantId + "/pump";
}

std::string Comms::getPublishTopic(std::string plantId)
{
  return "/esp-plant-sensor/" + plantId + "/moisture";
}

void Comms::addTopic(std::string id, std::function<void(std::string)> handler)
{
  topics.push_back(Topic{id, handler});
}

void onMqttConnect(esp_mqtt_client_handle_t client)
{
  if (Comms::mqttClient.isMyTurn(client))
  {
    // loop over topics, subscribe and setup topic handler
    for (int i = 0; i != topics.size(); ++i)
    {
      Comms::mqttClient.subscribe(
          topics[i].id,
          [&i](const std::string &payload)
          {
            topics[i].handler(payload);
          });
    }
  }
}

esp_err_t handleMQTT(esp_mqtt_event_handle_t event)
{
  Comms::mqttClient.onEventCallback(event);
  return ESP_OK;
}
