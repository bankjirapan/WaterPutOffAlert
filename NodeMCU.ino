#define BLYNK_PRINT Serial
#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//LCD Display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

//WiFi Mananger
WiFiManager wifiManager;

// Variable
const int pingPIN = 12;
const int trigerPIN = 13;
char blynkToken[] = "fe1f8af3e06747aeba411796d1abc4c7";


void setup()
{
  Serial.begin(115200);
  wifiManager.autoConnect("llUJO-IOT", "bankbank");
  wifiManager.setAPCallback(configModeCallback);
  WiFiManagerParameter customBlynkToken("Blynk", "blynk token", blynkToken, 34);
  wifiManager.addParameter(&customBlynkToken);
  wifiManager.autoConnect("Blynk");
  Blynk.config(customBlynkToken.getValue());
  Serial.print("Blynk Token : ");
  Serial.println(blynkToken);
  Blynk.config(blynkToken);
}


void configModeCallback (WiFiManager *myWiFiManager) {
  lcd.setCursor(0, 0);
  lcd.print("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

long runUltraSonic() {
  long duration;
  pinMode(pingPIN, OUTPUT);
  digitalWrite(pingPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPIN, LOW);
  pinMode(trigerPIN, INPUT);
  duration = pulseIn(trigerPIN, HIGH);
  return (duration / 29)/2;
}

void loop()
{
  Blynk.run();

  long rssi = WiFi.RSSI();
  Blynk.virtualWrite(10, runUltraSonic());
  Blynk.virtualWrite(V5, rssi);
// Delay 5s
  delay(5000);


}
