#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoLowPower.h>

// Define the display width and height
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Define the I2C address of the display
#define OLED_ADDR   0x3C // Change this if your display has a different address

// Create an Adafruit_SSD1306 object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
uint8_t brightness = 1;   //The brightness to set the LED to when the button is pushed

void setup() {
  // Initialize the display
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1); // Don't proceed, loop forever
  }
  display.clearDisplay();
  // Set text size and color
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.display();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 
}

void loop() {
  display.clearDisplay();  //Clear the display buffer
  display.setCursor(0,0);
  display.display();
  delay(5000);
  digitalWrite(LED_BUILTIN, LOW); // Show we're asleep
  LowPower.sleep(5000);
  digitalWrite(LED_BUILTIN, HIGH); // Show we're awake
}


