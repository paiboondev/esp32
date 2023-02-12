#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_SHT31.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("SHT31 test");
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
}

void loop() {
    float t = sht31.readTemperature();
    float h = sht31.readHumidity();
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    //บรรทัดที่ 1 
    display.setCursor(0, 10);   //แนวนอน 10 แนวตั้ง 10
    display.println("T: ");  
    display.setCursor(30, 10);  //แนวนอน 10 แนวตั้ง 30
    display.print(t);
    display.print(" C"); 
    //บรรทัดที่ 2 
    display.setCursor(0, 30);   //แนวนอน 30 แนวตั้ง 0
    display.println("H:");     
    display.setCursor(30, 30);  //แนวนอน 30 แนวตั้ง 30
    display.print(h);  
    display.print(" %"); 

    //แสดงข้อความ  
    display.display(); 
    delay(2000);
}
