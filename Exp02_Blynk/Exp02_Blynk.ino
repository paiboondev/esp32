/*************************************************************
  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPXXXXXXXXXX"
#define BLYNK_DEVICE_NAME "LBTechIOT"
#define BLYNK_AUTH_TOKEN "XXXXXXXXXXXXXXXXXXXXXXXXXX"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_SHT31.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SHT31 sht31 = Adafruit_SHT31();

#define relayPin01 32
#define relayPin02 14

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "XXXXXXXXXXX";
char pass[] = "XXXXXXXXXXXX";

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V1)
{
  int value = param.asInt();
  Serial.println("V1:[" + String(value) + "]");
  digitalWrite(relayPin01, !(value));
}
BLYNK_WRITE(V2)
{
  int value = param.asInt();
  Serial.println("V2:[" + String(value) + "]");
  digitalWrite(relayPin02, !(value));
}
void myTimerEvent()
{
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();
  if (isnan(t) || isnan(h)) {  // check if 'is not a number'
    Serial.println("Failed to read temperature");
  }
  else {
    String sht = "Temp : " + String(t) + " °C, Humd : " + String(h) + " %";
    Serial.println(sht);
    Blynk.virtualWrite(V3, t);
    Blynk.virtualWrite(V4, h);
  }
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
  //บรรทัดที่ 3
  display.setCursor(0, 50);   //แนวนอน 50 แนวตั้ง 0
  display.print("S1:");
  display.print(!(digitalRead(relayPin01)));
  display.print(" S2:");
  display.print(!(digitalRead(relayPin02)));
  //แสดงข้อความ
  display.display();
  delay(2000);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  delay(200);
  pinMode(relayPin01, OUTPUT);
  pinMode(relayPin02, OUTPUT);
  digitalWrite(relayPin01, HIGH);
  digitalWrite(relayPin02, HIGH);
  if (! sht31.begin(0x44)) {    // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
}
