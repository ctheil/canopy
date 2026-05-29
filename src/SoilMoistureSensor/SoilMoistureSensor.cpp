#include "SoilMoistureSensor.h"
#include "../Comms/Comms.h"
#include "Arduino.h"
#include <string>

SoilMoistureSensor::SoilMoistureSensor(int sensorPin, std::string plantId, Comms &c)
    : pin{sensorPin}, id{plantId}, comms{c} {}

int SoilMoistureSensor::getMoisturePercentage()
{
  const auto sensorValue = analogRead(pin);
  // Convert analog reading to percentage
  int soilMoisturePercent = map(sensorValue, airValue, waterValue, 0, 100);

  // Constrain limits to avoid getting >100% or <0% in extreme conditions
  soilMoisturePercent = constrain(soilMoisturePercent, 0, 100);
  return soilMoisturePercent;
}

void SoilMoistureSensor::publish(char buffer[64])
{
  comms.mqttClient.publish(Comms::getPublishTopic(id), buffer,
                           0, false);
}
