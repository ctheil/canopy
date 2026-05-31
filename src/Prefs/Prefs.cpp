#include "../Comms/Comms.h"
#include "Prefs.h"
#include <string>

float Prefs::publishFrequencyMinutes = 15.0;

void Prefs::setup()
{

  Comms::addTopic("/canopy/did1/preferences/publish-freq", [&](std::string payload)
                  { Prefs::publishFrequencyMinutes = std::stof(payload); });
}