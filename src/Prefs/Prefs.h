#pragma once

#include "../Comms/Comms.h"
#include <string>
#include <Preferences.h>
// struct PrefKeys
// {
//   char *deviceId, *publishFreq, *wifiSsid, *wifiPassword;
// };
struct FlashPref
{
  char *key, *value;
};

struct Pref
{
  char *flashKey, char *
};
class Prefs
{
public:
  static void setup();
  static float publishFrequencyMinutes;
  static std::string deviceId;
  static void publishState();

private:
  static void syncWithFlash();
  inline static std::vector<FlashPref> flashPrefs = {
      FlashPref{"device-id", "deviceId"},
      FlashPref{"publish-frequency", "publish-frequency"},
  };
  // inline static PrefKeys pkeys{
  //   deviceId : "device-id",
  //   publishFreq : "publish-frequency",
  //   wifiSsid : "wifi-ssid",
  //   wifiPassword : "wifi-password"
  // };
};