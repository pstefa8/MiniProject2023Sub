#include <SPI.h>
#include <SD.h>
#include <ArduinoLowPower.h>

#define PIN_SPI_CS 10

File myFile;

void setup() {
  Serial.begin(115200);
  if (!SD.begin(PIN_SPI_CS)) {
    Serial.println(F("SD CARD FAILED, OR NOT PRESENT!"));
    while (1); // don't do anything more:
  }
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 
}

void loop() {
  myFile = SD.open("Done.txt", FILE_WRITE);
  for(int i=0; i<1000000; i++)
  {
    myFile.println("done.");
  }
  myFile.close();
  digitalWrite(LED_BUILTIN, LOW); // Show we're asleep
  LowPower.sleep(5000);
  digitalWrite(LED_BUILTIN, HIGH); // Show we're awake
}
