
#ifndef SENSORI_H
#define SENSORI_H
#include <vector>
#include "common.h"
class SENSORI {  
public:              
  struct Measurement {
    float Pressure{ 0.f };
    float Altitude{ 0.f };
    float Temperature{ 0.f };
  };
  size_t Size() const;
  void SetVectorMaxSize(size_t vectorMaxSize);
  size_t GetIndex() const;
  float GetPressure(size_t index) const;
  float GetAltitude(size_t index) const;
  float GetTemperature(size_t index) const;
  void SetMakeMeasurement();
  void writeMeasurementsToSD(const char* filename) const;
  void UpdateDisplay() const;
  void DeleteVector();
private:
  size_t Index {0};
  size_t VectorMaxSize;
  std::vector<Measurement> Measurements;
  struct Measurement NewMeasurement;
};
#endif