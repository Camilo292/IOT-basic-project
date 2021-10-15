#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"

// Wifi credentials
const char *ssid = "Wifi name";
const char *password = "Wifi password";

// Firebase credentials
const char *FIREBASE_HOST = "https://esp32-controller-dd8ce-default-rtdb.firebaseio.com";
const char *FIREBASE_AUTH = "Hnh71bnbtKyHMLxH8GkhM0uJkrAFjPRcpAn1oTgp";

// Firebase Data object in the global scope
FirebaseData firebaseData;

//Define Firebase Data object
FirebaseData fbdo;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(250);
  }
  Serial.print("\nConecting to Wifi");
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  if (!Firebase.beginStream(fbdo, "integratedLed/state"))
    Serial.printf("sream begin error, %s\n\n", fbdo.errorReason().c_str());
}

void loop()
{
  if (Firebase.ready())
  {
    if (!Firebase.readStream(fbdo))
      Serial.printf("sream read error, %s\n\n", fbdo.errorReason().c_str());

    if (fbdo.streamTimeout())
    {
      Serial.println("stream timed out, resuming...\n");

      if (!fbdo.httpConnected())
        Serial.printf("error code: %d, reason: %s\n\n", fbdo.httpCode(), fbdo.errorReason().c_str());
    }

    if (fbdo.streamAvailable())
    {
      Serial.printf("sream path, %s\nevent path, %s\ndata type, %s\nevent type, %s\nvalue, %s\n\n",
                    fbdo.streamPath().c_str(),
                    fbdo.dataPath().c_str(),
                    fbdo.dataType().c_str(),
                    fbdo.eventType().c_str(),
                    fbdo.stringData().c_str());
    }
  }
}