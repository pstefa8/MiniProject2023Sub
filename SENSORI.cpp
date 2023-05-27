#include <cstddef>
#include "SENSORI.h"

void SENSORI::SetVectorMaxSize(size_t vectorMaxSize)
{
  VectorMaxSize = vectorMaxSize;
}

size_t SENSORI::Size() const
{
  return Measurements.size();
}

size_t SENSORI::GetIndex() const
{
  return Index;
}

float SENSORI::GetPressure(size_t index) const
{
  return Measurements.at(index).Pressure;
}

float SENSORI::GetAltitude(size_t index) const
{
  return Measurements.at(index).Altitude;
}

float SENSORI::GetTemperature(size_t index) const
{
  return Measurements.at(index).Temperature;
}

void SENSORI::writeMeasurementsToSD(const char *filename) const
{
  File myFile = SD.open(filename, FILE_WRITE);
  if (myFile)
  {
    for (size_t k = 0; k < VectorMaxSize; k++)
    {
      myFile.print(this->GetPressure(k));
      myFile.print(", ");
      myFile.print(this->GetAltitude(k));
      myFile.print(", ");
      myFile.println(this->GetTemperature(k));
    }
    myFile.close();
    Serial.println("done.");
  }
  else
  {
    Serial.println("error opening text file");
  }
}

void SENSORI::SetMakeMeasurement()
{
  // units: hPa, m, C
  if (this->Size() == VectorMaxSize)
    Measurements.erase(Measurements.begin());
  NewMeasurement.Pressure = baro.getPressure();
  NewMeasurement.Altitude = baro.getAltitude();
  NewMeasurement.Temperature = baro.getTemperature();
  Measurements.push_back(NewMeasurement);
  Index = this->Size() - 1;
}

void SENSORI::UpdateDisplay() const
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("pre = ");
  display.print(NewMeasurement.Pressure);
  display.println(" hPa");
  display.print("alt = ");
  display.print(NewMeasurement.Altitude);
  display.println(" m");
  display.print("tem = ");
  display.print(NewMeasurement.Temperature);
  display.println(" C");
  display.print("Ind = ");
  display.print(Index);
  display.display();
}

void SENSORI::DeleteVector()
{
  Measurements.clear();
}