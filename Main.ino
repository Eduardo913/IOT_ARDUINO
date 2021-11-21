


#include <Arduino.h>
#include "WifiScript.h"

#include <common.h>
#include <Firebase.h>
#include <FirebaseESP8266.h>
#include <FirebaseFS.h>
#include <Utils.h>
#include <Ticker.h>

const char *FIREBASE_HOST = "iot-eduardo-default-rtdb.firebaseio.com";
const char *FIREBASE_AUTH = "aEcmZDKckfRM3riyIJ7FPjYKwTJ0QZtz1RNWkBTV";

String path = "/MyHome";

FirebaseData firebaseData;

boolean BoolVerificar = false;

#define LED1 D2

int EstadoLed;


Ticker timer;

void setup() {
    Serial.begin(115200);
    // pines a usar 
    pinMode(LED1,OUTPUT);
    EstadoLed = 0;
    timer.attach(4,funcion_1);
    // conexion a internet
    initConnection(); //WifiScript

    //conexion a socket
    Serial.println("Conectando al servidor");

    Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);

}

void loop() {

  if(BoolVerificar == true){
    BoolVerificar = false;
    if(Firebase.getInt(firebaseData,path + "/Dispositivo/Luz_1")){
      int data = firebaseData.to<int>();
      if(data != EstadoLed){
        Serial.println("el valor del led a cambiado");
        EstadoLed = data;
        digitalWrite(LED1,EstadoLed);
      }
    }else{
      Serial.println("no es un entero");
    }
    
  }
  
}

void funcion_1(){
  BoolVerificar = true;
}
