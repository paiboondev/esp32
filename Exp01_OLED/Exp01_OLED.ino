#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_SHT31.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup() {
  Serial.begin(115200);
  delay(2000);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
}

void loop() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    //บรรทัดที่ 1 
    display.setCursor(0, 10);   //แนวนอน 10 แนวตั้ง 10
    display.println("Hello iOT!! ");  
    //บรรทัดที่ 2 
    display.setCursor(0, 30);   //แนวนอน 30 แนวตั้ง 0
    display.println("Paiboon");     

    //แสดงข้อความ  
    display.display(); 
    delay(2000);
}
