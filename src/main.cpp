///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUDES
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "./Prefs/Prefs.h"
#include "./Comms/Comms.h"
#include "./SoilMoistureSensor/SoilMoistureSensor.h"
#include "Arduino.h"
#include "./Pump/Pump.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// GLOBALS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t loopCount = 0;

SoilMoistureSensor sensors[] = {SoilMoistureSensor(32, "001"), SoilMoistureSensor(33, "002"), SoilMoistureSensor(34, "003")};
int constexpr numSensors = sizeof(sensors) / sizeof(sensors[0]);

Pump fertPump(19, 21, 18); // PWM AI1 AI2

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// STRUCTS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ProgramInfo
{
  std::string version;
  int isDevelopment;
} pinfo = ProgramInfo{"v0.0.04", 0};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int shouldPublish(uint32_t loopCount, const float &minutes = Prefs::publishFrequencyMinutes, int skip = pinfo.isDevelopment)
{
  return !skip && loopCount >= 1000 * 60 * minutes;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// MAIN
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(115200);

  Prefs::setup();
  Comms::setup();
  fertPump.setup();

  log_i("\nversion: %s DEV: %d", pinfo.version.c_str(), pinfo.isDevelopment);
}

float readBatteryVoltage()
{
  int raw = analogReadMilliVolts(34); // GPIO34, returns mV
  float vout = raw / 1000.0;          // convert to volts
  float vbat = vout * 2.0;            // multiply by (R1+R2)/R2 = 200k/100k = 2
  return vbat;
}

void loop()
{

  if (shouldPublish(loopCount, Prefs::publishFrequencyMinutes, pinfo.isDevelopment))
  {
    auto batt = readBatteryVoltage();
    Comms::mqttClient.publish(Comms::endpoint("/battery").c_str(), 1, true, std::to_string(batt).c_str());

    // loop over every sensor and publish to its topic id
    for (int i = 0; i != numSensors; ++i)
    {
      const int moisturePercentage = sensors[i].getMoisturePercentage();
      char buffer[64];
      snprintf(buffer, sizeof(buffer), "{\"soil-moisture\": %d}",
               moisturePercentage);
      sensors[i].publish(buffer);
    }
    loopCount = 0;
  }
  ++loopCount;
  delay(1);
}
