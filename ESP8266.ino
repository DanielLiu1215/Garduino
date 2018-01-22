void setupEsp8266() {
  wdt_reset();
  lcd.clear();
  lcd.home();
  lcd.print(F("Initalizing ESP8266"));
  DEBUG_PRINTLN(F("Initalizing ESP8266..."));
  espSeiral_Flush();
  espSeiral_Println(F("AT+CWAUTOCONN=0"));
  espSeiral_Flush();
  delay(500);
  espSeiral_Println(F("AT+RST"));
  espSeiral_Flush();
  delay(5000);
  wdt_reset();
  espSeiral_Println(F("AT+CWMODE_CUR=1"));
  espSeiral_Flush();
  delay(500);
  char atSend[70];
  sprintf(atSend, "AT+CWJAP_CUR=\"%s\",\"%s\",\"%s\"\r\n", WiFi_SSID, WiFi_password, AP_MAC);
  DEBUG_PRINT(atSend);
  espSeiral_Print(atSend);
  espSeiral_Flush();
  delay(2000);
  wdt_reset();
  espSeiral_ReadString();
}

int checkEsp8266Status() {
  wdt_reset();
  lcd.clear();
  lcd.home();
  lcd.print(F("Checking internet"));
  lcd.setCursor(0, 1);
  lcd.print(F("connection..."));
  DEBUG_PRINTLN(F("Checking internet connection..."));
  espSeiral_Println(F("AT+CIPCLOSE"));
  espSeiral_Flush();
  espSeiral_ReadString();
  espSeiral_Println(F("AT+CIPSTATUS"));
  espSeiral_Flush();
//  DEBUG_PRINTLN(espSeiral_ReadString());
  if (espSeiral_Find("AT+CIPSTATUS") && espSeiral_Find("STATUS:")) {
    int atCipStatus = espSeiral_ParseInt();
    if (atCipStatus == 2 || atCipStatus == 4) {
      DEBUG_PRINTLN(F("Network status OK"));
      return 0;
    } else {
      DEBUG_PRINTLN(F("Connection error, restarting..."));
      return -2;
    }
  } else {
    DEBUG_PRINTLN(F("Can't find \"AT+CIPSTATUS\", restarting..."));
    return -1;
  }
}

void updateChannelFeed() {
  int statusFlag;
  wdt_reset();
  unsigned long oldTime = millis();
  while (checkEsp8266Status() != 0) {
    setupEsp8266();
  }
  lcd.clear();
  lcd.home();
  lcd.print(F("Uploading feed..."));
  collectData();
  char atCmd[40];
  sprintf(atCmd, "AT+CIPSTART=\"TCP\",\"%s\",80", ThingSpeak_IP);
  espSeiral_Println(atCmd);
  if (espSeiral_Find("CONNECT")) {
    DEBUG_PRINTLN(F("Connected to server"));
    char atSend[125];
    sprintf(atSend, "GET /update?key=%s&field1=%d&field2=%d&field3=%d&field4=%d&field5=%d&field6=%d&field7=%d&field8=%d\r\n",
            WriteAPIKey, temp, humi, dhtChk, moist1, moist2, light, timeForUpload, waterSwitch);
    espSeiral_Print("AT+CIPSEND=");
    espSeiral_Println(strlen(atSend));
    if (espSeiral_Find(">")) {
      espSeiral_Print(atSend);
      DEBUG_PRINT(atSend);
      espSeiral_Flush();
      delay(500);
      if (espSeiral_Find("SEND OK\r\n\r\n+IPD,")) {
        DEBUG_PRINTLN(F("Data sent"));
        statusFlag = 0;
      } else {
        printEsp8266Message();
        DEBUG_PRINTLN(F("Error while sending data"));
        statusFlag = -3;
      }
    } else {
      printEsp8266Message();
      DEBUG_PRINTLN(F("Unable to send feeds"));
      statusFlag = -2;
    }
  } else {
    printEsp8266Message();
    DEBUG_PRINTLN(F("ERROR while connecting to server"));
    statusFlag = -1;
  }
  readResponse();
  //  printEsp8266Message();
  timeForUpload = millis() - oldTime;
  DEBUG_PRINT(timeForUpload / 1000.0);
  DEBUG_PRINT("sec\r\n\r\n");
  lastUploadTime = millis();
  screenUpdate();
}

void readResponse() {
  int i = espSeiral_ParseInt();
  char responseBuffer[(i + 1)];
  espSeiral_Read();
  for (int j = 0; j < i; j++) {
    responseBuffer[j] = espSeiral_Read();
  }
  responseBuffer[i] = '\0';
  DEBUG_PRINT(F("Character recieved: "));
  DEBUG_PRINTLN(i);
  DEBUG_PRINT(F("Message: "));
  DEBUG_PRINTLN(responseBuffer);
}

void printEsp8266Message() {
  char c;
  while (espSeiral_Available()) {
    c = espSeiral_Read();
    DEBUG_PRINT(c);
  }
}
