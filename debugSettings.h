//esp8266 serial
#include <AltSoftSerial.h>
AltSoftSerial esp8266Serial; //RX: pin8, TX: pin9
#define espSeiral_Begin()       esp8266Serial.begin(19200)
#define espSeiral_Available()   esp8266Serial.available()
#define espSeiral_Flush()       esp8266Serial.flush()
#define espSeiral_Print(...)    esp8266Serial.print(__VA_ARGS__)
#define espSeiral_Println(...)  esp8266Serial.println(__VA_ARGS__)
#define espSeiral_ReadString()  esp8266Serial.readString()
#define espSeiral_Find(...)     esp8266Serial.find(__VA_ARGS__)
#define espSeiral_ParseInt()    esp8266Serial.parseInt()
#define espSeiral_Read()        esp8266Serial.read()

//debug serial
#define DEBUG_BEGIN()           Serial.begin(19200)
#define DEBUG_PRINT(...)        Serial.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...)      Serial.println(__VA_ARGS__)

//pin set
#define buttonPin 3
#define buttonLEDPin 11   //LOW active
#define relay 13    //LOW active
#define moistureSensorPower1 5
#define moistureSensorPower2 6
#define moistureSensor1 A0
#define moistureSensor2 A1
#define lightSensor A2
#define dhtPin 10

//APIKeys
#define WriteAPIKey "3LNKIS4CEY9S9136"
#define TalkBackAPIKey "OIUU4HWWI9CKCJQ0"
#define TalkBackID "17923"
