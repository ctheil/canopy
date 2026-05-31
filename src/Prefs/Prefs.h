#pragma once

#include "../Comms/Comms.h"
#include <string>

class Prefs
{
public:
  static void setup();
  static float publishFrequencyMinutes;
};
