#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// Define the display width and height
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Define the I2C address of the display
#define OLED_ADDR   0x3C // Change this if your display has a different address

// Create an Adafruit_SSD1306 object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

bool displayState=false;


void setup() {
  Serial.begin (115200);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), interrupt, RISING);
}

void loop() {

}

void interrupt()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) 
  {
     Serial.println("pressed");
    if(displayState==false)//if the display was off when the button was pressed -> turn on
    {
      Serial.println("pressed when off");
        displayState=true;
        digitalWrite(3, LOW);
        if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
          Serial.println(F("SSD1306 allocation failed"));
          while (1); // Don't proceed, loop forever
        }
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0,0);
        display.println("HELLO55555"); 
        display.print("HELLO55555"); 
        display.display();
    }
    else
    {
      Serial.println("pressed when on");
        displayState=false;
        digitalWrite(3, HIGH);
    }
  }
  last_interrupt_time = interrupt_time;
}


