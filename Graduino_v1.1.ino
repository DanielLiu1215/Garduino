#include <dht.h>
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
#include <Time.h>         //http://www.arduino.cc/playground/Code/Time  
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire
#include <TimeLib.h>
#include <LiquidCrystal_I2C.h> //https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home
#include <avr/wdt.h>
#include "settings.h"

//#define DEBUG

#ifdef DEBUG
  #include "debugSettings.h"
#else
  #include "normalSettings.h"
#endif

boolean waterSwitch = false;
boolean oldWaterSwitch = false;
boolean displayType = 0;
boolean backlight = true;
boolean buttonTrigger = false;
boolean buttonLED = LOW;
int temp, humi, dhtChk, moist1, moist2, light;
unsigned int timeForUpload = 0;
unsigned long lastUploadTime;
unsigned long lastLcdUpdateTime;
unsigned long floweringTime;
unsigned long buttonTriggerTime;
unsigned long backlightTime;
unsigned long buttonLEDOnTime = 0;

//                     addr,en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C  lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
dht DHT;

void setup() {
  wdt_disable();
  wdt_enable(WDTO_8S);
  lcd.begin (20, 4);
  lcd.setBacklight(backlight);
  lcd.print("Initalizing...");

  DEBUG_BEGIN();
  espSeiral_Begin();
  delay(500);

  setupEsp8266();

  RTC.setAlarm(ALM2_MATCH_MINUTES, 0, 0, 1, 1);

  pinMode(buttonPin, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, !waterSwitch);
  pinMode(buttonLEDPin, OUTPUT);
  pinMode(moistureSensorPower1, OUTPUT);
  pinMode(moistureSensorPower2, OUTPUT);

  updateChannelFeed();
  screenUpdate();
  backlightTime = millis();
}

void loop() {
  checkButtom(buttonPin);
  triggeredIndication();
  flowering();

  if (!buttonTrigger) {
    if (millis() - lastUploadTime > uploadFrequency * (unsigned long)1000) {
      updateChannelFeed();
    }
    if (millis() - lastLcdUpdateTime > lcdUpdateFrequency) {
      screenUpdate();
    }
  }
  wdt_reset();
}
