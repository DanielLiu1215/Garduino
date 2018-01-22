void screenUpdate() {
  displayType = !displayType;
  lcd.clear();
  lcd.home();
  lcd.print(F("Graduino System"));
  if (displayType == 1) {
    lcd.setCursor(0, 1);
    lcd.print(F("Temp:"));
    lcd.setCursor(6, 1);
    lcd.print(temp);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(13, 1);
    lcd.print(F("RH:"));
    lcd.setCursor(17, 1);
    lcd.print(humi);
    lcd.print(F("%"));
    lcd.setCursor(0, 2);
    lcd.print(F("Soil Moisture 1:"));
    lcd.setCursor(17, 2);
    lcd.print(moist1);
    lcd.print(F("%"));
  } else {
    lcd.setCursor(0, 1);
    lcd.print(F("Light:"));
    lcd.setCursor(7, 1);
    lcd.print(light);
    lcd.print(F("%"));
    lcd.setCursor(0, 2);
    lcd.print(F("Soil Moisture 2:"));
    lcd.setCursor (17, 2);
    lcd.print(moist2);
    lcd.print(F("%"));
  }
  lcd.setCursor (0, 3);
  lcd.print(F("Water Switch:"));
  if (waterSwitch == true) {
    lcd.setCursor(18, 3);
    lcd.print(F("ON"));
  } else {
    lcd.setCursor(17, 3);
    lcd.print(F("OFF"));
  }
  if (backlight && (millis() - backlightTime) >= backlightTimeLimit) {
    backlight = false;
    lcd.setBacklight(backlight);
  }
  lastLcdUpdateTime = millis();
}
