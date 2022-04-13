#include <Arduino.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define API_KEY "AIzaSyAYtcFONyqV9laJcmmdWi1FlUpCF6YqzKI";
#define DATABASE_URL "pollution-detector-nodemcu-default-rtdb.asia-southeast1.firebasedatabase.app";

int ledPin = 2;

const char *ssid = "Kush";
const char *pass = "kushkush";

int PulseSensorPurplePin = A0;
int Signal;
int Threshold = 550;

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

float value1;
int value2;

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
    Serial.println("ok");
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
  
  
  if(Firebase.ready() && signupOK) {
    Signal = analogRead(PulseSensorPurplePin);
    Serial.println(Signal);
    delay(1000);
    Firebase.RTDB.setInt(&fbdo, "Pulse", Signal);
  }
  
  //
  //  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  //  //Serial.println("High");
  //  delay(1000);               // wait for a second
  //  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  //  //Serial.println("Low");
  //  delay(1000);               // wait for a second

  /*if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    value1 = random(0, 100) + 0.1 * random(0, 100) + 0.01 * random(0, 100);
    value2 = count;
    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setInt(&fbdo, "Polution-Index/CO2", value2))
    {
      Serial.println();
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
      Serial.println("VALUE: " + String(value2));
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    count++;

    // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "Polution-Index/CO", value1))
    {
      Serial.println();
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
      Serial.println("VALUE: " + String(value1));
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }*/

}
