int dhtMeasure() {
  int chk;
  chk = DHT.read11(dhtPin);
  temp = (int)DHT.temperature;
  humi = (int)DHT.humidity;
  if (chk != DHTLIB_OK) {
    temp = -1;
    humi = -1;
    DEBUG_PRINT(F("DHT Error: "));
    DEBUG_PRINTLN(chk);
  }
  return chk;
}

int moistureMeasrue(int analogPin, int powerPin) {
  digitalWrite(powerPin, HIGH);
  delay(50);
  analogRead(analogPin);
  int moist = 0;
  for (int i = 0; i < 10; i++) {
    moist += analogRead(analogPin);
  }
  digitalWrite(powerPin, LOW);
  return map(moist / 10, 0, 1023, 0, 100);
}

void collectData() {
  dhtChk = dhtMeasure();
  #ifdef FRONTYARD
    moist1 = moistureMeasrue(moistureSensor1, moistureSensorPower1);
    light = map((analogRead(lightSensor)*(long)96), 0, 102300, 0, 100); //offset for a different photoresistor
  #else
    moist1 = moistureMeasrue(moistureSensor1, moistureSensorPower1);
    moist2 = moistureMeasrue(moistureSensor2, moistureSensorPower2);
    light = map(analogRead(lightSensor), 0, 1023, 0, 100);
  #endif
}

void checkButtom(int pin) {
  if (digitalRead(pin)) {
    buttonTrigger = !buttonTrigger;
    buttonTriggerTime = millis();
    backlight = true;
    backlightTime = millis();
    DEBUG_PRINTLN("button pressed");
    lcd.setBacklight(backlight);
    lcd.clear();
    if (buttonTrigger) {
      if (waterSwitch) {
        lcd.home();
        lcd.print(F("Water will turn OFF"));
        lcd.setCursor(0, 2);
        lcd.print(F("in 10 seconds"));
      } else {
        lcd.home();
        lcd.print(F("Water will turn ON"));
        lcd.setCursor(0, 2);
        lcd.print(F("in 10 seconds"));
      }
    } else {
      screenUpdate();
    }
    delay(100);
  }
}
