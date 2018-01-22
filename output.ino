void flowering() {
  if (RTC.alarm(ALARM_2) && !waterSwitch) {
    moist1 = moistureMeasrue(moistureSensor1, moistureSensorPower1);
    moist2 = moistureMeasrue(moistureSensor2, moistureSensorPower2);
    tmElements_t curTime;
    RTC.read(curTime);
    int curHour = curTime.Hour;
    if (curHour == 6 || curHour == 8 || curHour == 16 || curHour == 18) {
      if (moist1 <= dry || moist2 <= dry){
        waterSwitch = true;
        floweringTime = millis();
      }
    }
  } else if (buttonTrigger) {
    if ((millis() - buttonTriggerTime) >= manualTriggerDelay) {
      lcd.clear();
      if (!waterSwitch) {
        waterSwitch = true;
        floweringTime = millis();
      } else {
        waterSwitch = false;
      }
      buttonTrigger = false;
      triggeredIndication();
      wdt_reset(); 
    }
  } else if (waterSwitch) {
    moist1 = moistureMeasrue(moistureSensor1, moistureSensorPower1);
    moist2 = moistureMeasrue(moistureSensor2, moistureSensorPower2);
    if (moist1 >= wet || moist2 >= wet || (millis() - floweringTime) >= (maxFloweringTime * (unsigned long)1000)) {
      waterSwitch = false;
    }
  }
  
  digitalWrite(relay, !waterSwitch);
  
  if (oldWaterSwitch != waterSwitch) {
    oldWaterSwitch = waterSwitch;
    updateChannelFeed();
    lastUploadTime = millis();
    lcd.clear();
    if (waterSwitch) {
      lcd.home();
      lcd.print(F("Water is turned ON"));
    } else {
      lcd.home();
      lcd.print(F("Water is turned OFF"));
    }
    lastLcdUpdateTime = millis();
  }
}

void triggeredIndication() {
  if (buttonTrigger) {
    if ((millis() - buttonLEDOnTime) >= buttonBlinkSpeed) {
      buttonLEDOnTime = millis();
      buttonLED = !buttonLED;
    }
  } else {
    buttonLED = waterSwitch;
  }
  digitalWrite(buttonLEDPin, buttonLED);
}
