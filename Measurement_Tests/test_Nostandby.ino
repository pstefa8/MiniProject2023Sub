#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
#include <ArduinoLowPower.h>

#define MPL3115A2_CIRL_REGI 0X26 // Control register 1
Adafruit_MPL3115A2 baro;
void setup()
{
  Wire.begin(); // Initialize I2C
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // Show we're awake
  if (!baro.begin()) {
    Serial.println("Could not find sensor. Check wiring.");
    while(1);
  }
  // use to set sea level pressure for current location
  // this is needed for accurate altitude measurement
  // STD SLP = 1013.26 hPa
  baro.setSeaPressure(1036);
}


void loop() {
  float pressure = baro.getPressure(); //" hPa"
  float altitude = baro.getAltitude(); //" m"
  float temperature = baro.getTemperature(); //" C"
  Serial.print("pressure = "); Serial.print(pressure); Serial.println(" hPa");
  Serial.print("altitude = "); Serial.print(altitude); Serial.println(" m");
  Serial.print("temperature = "); Serial.print(temperature); Serial.println(" C");
  Serial.println("-----------------------------------");
  digitalWrite(LED_BUILTIN, LOW); // Show we're asleep
  LowPower.sleep(5000);
  digitalWrite(LED_BUILTIN, HIGH); // Show we're awake
}