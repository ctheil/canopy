#pragma once

#include "../Comms/Comms.h"
#include <string>
#include <Preferences.h>

class Prefs
{
public:
  static void setup();
  static float publishFrequencyMinutes;
  static std::string deviceId;
};
