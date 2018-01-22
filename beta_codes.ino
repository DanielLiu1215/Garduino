/**************************CODES_FOR_TESTING********************************
  void checkMoiBeta(){
  digitalWrite(moistureSensorPower1, HIGH);
  delay(50);
  moist1 = 0;
  analogRead(moistureSensor1);
  for(int i=0; i<10; i++){
    int moist = analogRead(moistureSensor1);
    Serial.print(moist);
    Serial.print("\t");
    moist1 += moist;
  }
  moist1 = map(moist1/10, 0, 1023, 0, 100);
  //digitalWrite(moistureSensorPower1, LOW);
  Serial.println(moist1);
  }


******************************************************************************/
