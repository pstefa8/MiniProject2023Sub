#include <ArduinoLowPower.h>
#include "SENSORI.h"
#include "common.h"

constexpr struct
{
  uint8_t ScreenWidth {128}; // OLED display width, in pixels
  uint8_t ScreenHeight {32}; // OLED display height, in pixels
  uint8_t OLEDAddress {0x3C};// Define the I2C address of the display
  pin_size_t CSPin {10};
  pin_size_t LEDPin {3};
  pin_size_t  ButtonPin {2};
  uint8_t charArraySize {100};
  long BaudRate {115200};
} LocalConstants;

class UserInput {
  public:
    float SeaLevelPressure;   
    uint32_t SleepTime;
    size_t VectorSize;
};

Adafruit_SSD1306 display(LocalConstants.ScreenWidth, LocalConstants.ScreenHeight, &Wire, -1);
Adafruit_MPL3115A2 baro;
SENSORI Sensor;  
UserInput Input;
volatile bool displayState = false;

void setup() {

  Serial.begin(LocalConstants.BaudRate);
  while (!Serial)
    ;
  Serial.flush(); 
  if (!SD.begin(LocalConstants.CSPin)) {
    Serial.println("initialization failed!");
    return;
  }
  
  char stringArray[LocalConstants.charArraySize];
  File inputFile = SD.open("Input.txt");
  if (inputFile) {
    uint8_t i=0;
    while (inputFile.available() && i<LocalConstants.charArraySize) {
      stringArray[i]=inputFile.read();
      i++;
    }
    stringArray[i]='\0';

    inputFile.close();

    String s = String(stringArray);
    Input.SeaLevelPressure = s.substring(0, s.indexOf(',')).toFloat();
    s = s.substring(s.indexOf(',') + 1);
    Input.SleepTime = s.substring(0, s.indexOf(',')).toInt();
    s = s.substring(s.indexOf(',') + 1);
    Input.VectorSize = s.toInt();

  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  if (!baro.begin()) {
    Serial.println("Could not find sensor. Check wiring.");
    while (1)
      ;
  }

  baro.setSeaPressure(Input.SeaLevelPressure);

  if (!display.begin(SSD1306_SWITCHCAPVCC, LocalConstants.OLEDAddress)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1)
      ;  
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.display();
  pinMode(LocalConstants.ButtonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LocalConstants.ButtonPin), interrupt, RISING);
  pinMode(LocalConstants.LEDPin, OUTPUT);
  digitalWrite(LocalConstants.LEDPin, HIGH);  
  Sensor.SetVectorMaxSize(Input.VectorSize);
}

void loop() {
  for (int k = 0; k < Input.VectorSize; k++) {
    Sensor.SetMakeMeasurement();
    Serial.print(k);
    Serial.print(" ");
    if (displayState == true) 
       Sensor.UpdateDisplay();
    digitalWrite(LocalConstants.LEDPin, LOW);
    LowPower.sleep(Input.SleepTime);
    digitalWrite(LocalConstants.LEDPin, HIGH);
  }
  Sensor.writeMeasurementsToSD("Output.txt");
  Sensor.DeleteVector();
}

void interrupt() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) {
    if (displayState == false)
    {
     // if the display cables lose connection
    if (!display.begin(SSD1306_SWITCHCAPVCC, LocalConstants.OLEDAddress)) {
      Serial.println(F("SSD1306 allocation failed"));
      while (1)
      ;
    }
      Sensor.UpdateDisplay();
      displayState = true;
    } else {
      display.clearDisplay();
      display.display();
      displayState = false;
    }
  }
  last_interrupt_time = interrupt_time;
}
