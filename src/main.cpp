///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUDES
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "./Comms/Comms.h"
#include "./SoilMoistureSensor/SoilMoistureSensor.h"
#include "./Pump/Pump.h"
#include "Arduino.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// GLOBALS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int loopCount = 0;
Comms c;
SoilMoistureSensor sensors[3] = {SoilMoistureSensor(32, "001"), SoilMoistureSensor(33, "002"), SoilMoistureSensor(34, "003")};
Pump fertPump(19, 21, 18);
int constexpr numSensors = sizeof(sensors) / sizeof(sensors[0]);

struct ProgramInfo
{
  std::string version;
  int isDevelopment;
} pinfo = ProgramInfo{"v0.0.02", 1};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// MAIN
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(115200);

  Comms::setupWifi();
  Comms::setupMqtt();

  fertPump.setup();

  log_i("\nversion: %s", pinfo.version);
}

int shouldPublish(const int &loopCount, const float &minutes = 15.0)
{
  return loopCount >= 1000 * 60 * minutes;
}

void loop()
{
  // publish ever 15 minutes
  if (shouldPublish(loopCount, 0.1))
  {
    log_i("LOOP");
    // // loop over every sensor and publish to its topic id
    // for (int i = 0; i != numSensors; ++i)
    // {
    //   const int moisturePercentage = sensors[i].getMoisturePercentage();
    //   char buffer[64];
    //   snprintf(buffer, sizeof(buffer), "{\"soil-moisture\": %d}",
    //            moisturePercentage);
    //   sensors[i].publish(buffer);
    // }
    // loopCount = 0;
  }
  ++loopCount;
}
