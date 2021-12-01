


#include <Arduino.h>
#include "WifiScript.h"

#include <common.h>
#include <Firebase.h>
#include <FirebaseESP8266.h>
#include <FirebaseFS.h>
#include <Utils.h>

const char *FIREBASE_HOST = "iot-eduardo-default-rtdb.firebaseio.com";
const char *FIREBASE_AUTH = "aEcmZDKckfRM3riyIJ7FPjYKwTJ0QZtz1RNWkBTV";

String path = "/MyHome";

FirebaseData firebaseData;

#define LED1 D2

int EstadoLed;


void setup() {
    Serial.begin(115200);
    // pines a usar 
    pinMode(LED1,OUTPUT);
    EstadoLed = 0;

    // conexion a internet
    initConnection(); //WifiScript

    //conexion a socket
    Serial.println("Conectando al servidor");

    Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);

    Firebase.setStreamCallback(firebaseData, streamCallback, streamTimeoutCallback);
    if (!Firebase.beginStream(firebaseData, path + "/Dispositivo/Luz_1")){
      Serial.println(firebaseData.errorReason());
    }


}

void loop() {

}

void streamCallback(StreamData data){
  
  if (data.dataTypeEnum() == fb_esp_rtdb_data_type_integer){
    int valor = data.to<int>();
      if(valor != EstadoLed){
        Serial.println("el valor del led a cambiado");
        EstadoLed = valor;
        digitalWrite(LED1,EstadoLed);
      }
  }
}


void streamTimeoutCallback(bool timeout)
{
  if(timeout){
    //Stream timeout occurred
    Serial.println("Stream timeout, resume streaming...");
  }
}