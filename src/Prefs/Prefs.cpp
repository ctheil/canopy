#include "../Comms/Comms.h"
#include "Prefs.h"
#include <string>
#include <Preferences.h>

Preferences flashPreferences;

float Prefs::publishFrequencyMinutes = 15.0;
std::string Prefs::deviceId = "untitled_dev_board";

void Prefs::setup()
{
  flashPreferences.begin("canopy", false);
  Prefs::deviceId = std::string(flashPreferences.getString("device-id").c_str());

  Comms::addTopic(Comms::endpoint("/preferences/publish-freq"), [&](std::string payload)
                  { Prefs::publishFrequencyMinutes = std::stof(payload); });
  Comms::addTopic(Comms::endpoint("/preferences/deviceId"), [&](std::string payload)
                  { flashPreferences.putString("device-id", payload.c_str()); Prefs::deviceId = payload; });
}