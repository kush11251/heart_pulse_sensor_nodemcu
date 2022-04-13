#include <Arduino.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define API_KEY "AIzaSyDnpQaYQrSxis9SPSoQjm4Gv__vMfZWfjQ";
#define DATABASE_URL "pulse-node-mcu-default-rtdb.firebaseio.com";

int ledPin = 2;

const char *ssid = "Kush";
const char *pass = "kushkush";

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

float value1;
int value2;

int age;
String gender;
String uname;
int pulse;
String userId;

WiFiClient client;

void setup() {
  Serial.begin(115200);

  int numberOfNetworks = WiFi.scanNetworks();

  for (int i = 0; i < numberOfNetworks; i++) {

    Serial.print("Network name: ");
    Serial.println(WiFi.SSID(i));
    Serial.print("Signal strength: ");
    Serial.println(WiFi.RSSI(i));
    Serial.println("-----------------------");

  }

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  //pinMode(ledPin, OUTPUT);

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Authenticated With Firebase");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

// the loop function runs over and over again forever
void loop() {

  //  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  //  //Serial.println("High");
  //  delay(1000);               // wait for a second
  //  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  //  //Serial.println("Low");
  //  delay(1000);               // wait for a second

  if(Firebase.ready() && signupOK) {
    Firebase.RTDB.getInt(&fbdo, "Pulse");
    pulse = fbdo.intData();

    Firebase.RTDB.getInt(&fbdo, "Age");
    age = fbdo.intData();
    
    Serial.println();
    Serial.println("AGE: " + String(age));
    Serial.println("PULSE: " + String(pulse));
  }

  /*if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getInt(&fbdo, "Polution-Index/CO2")) {
      if (fbdo.dataType() == "int") {
        value2 = fbdo.intData();

        Serial.println();
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
        Serial.println("VALUE: " + String(value2));
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getFloat(&fbdo, "Polution-Index/CO")) {
      if (fbdo.dataType() == "float") {
        value1 = fbdo.floatData();
        Serial.println();
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
        Serial.println("VALUE: " + String(value1));
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  }*/

}
