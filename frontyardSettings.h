//esp8266 serial
#define espSeiral_Begin()       Serial.begin(115200)
#define espSeiral_Available()   Serial.available()
#define espSeiral_Flush()       Serial.flush()
#define espSeiral_Print(...)    Serial.print(__VA_ARGS__)
#define espSeiral_Println(...)  Serial.println(__VA_ARGS__)
#define espSeiral_ReadString()  Serial.readString()
#define espSeiral_Find(...)     Serial.find(__VA_ARGS__)
#define espSeiral_ParseInt()    Serial.parseInt()
#define espSeiral_Read()        Serial.read()

//debug serial
#define DEBUG_BEGIN()
#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)

//pin set
#define buttonPin 4
#define buttonLEDPin 3  //LOW active
#define relay 10  //LOW active
#define moistureSensorPower1 11
#define moistureSensorPower2 12
#define moistureSensor1 A1
#define moistureSensor2 A2
#define lightSensor A0
#define dhtPin 6

//APIKeys
#define WriteAPIKey "WMJ2324E08A8XJN1"
