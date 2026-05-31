#include "../Comms/Comms.h"
#include "Prefs.h"
#include <string>
#include <Preferences.h>

Preferences flashPreferences;

float Prefs::publishFrequencyMinutes = 15.0;
std::string Prefs::deviceId = "untitled_dev_board"; // default

char *const DEVICE_ID_KEY = "device-id";

void Prefs::setup()
{
  flashPreferences.begin("canopy", false);
  std::string setId = std::string(flashPreferences.getString(DEVICE_ID_KEY).c_str());
  if (setId != "")
    Prefs::deviceId = setId;

  // add topics to put, update flash (if applicable), publish state update
  Comms::addTopic(Comms::endpoint("/preferences/put-publish-freq"), [&](std::string payload)
                  { Prefs::publishFrequencyMinutes = std::stof(payload); Prefs::publishState(); });
  Comms::addTopic(Comms::endpoint("/preferences/put-device-id"), [&](std::string payload)
                  { flashPreferences.putString(DEVICE_ID_KEY, payload.c_str()); Prefs::deviceId = payload; Prefs::publishState(); }); // WILL PUBLISH TO UPDATED DEVICE ID ENDPOINT... FIXME?
}

void Prefs::publishState()
{
  Comms::mqttClient.publish(
      Comms::endpoint("/preferences").c_str(),
      0,
      true, // retain
      std::string(std::to_string(Prefs::publishFrequencyMinutes) + "," + Prefs::deviceId).c_str());
}