#include <ESP8266WiFi.h>

#include <strings_en.h>
#include <WiFiManager.h>

WiFiManager wifiManager;

void connection(){
  if(!wifiManager.autoConnect("IOT_8266","12345678")){
    Serial.println("Fallo en Conexion a red");
    ESP.reset();
    delay(1000);
  }
  Serial.println("Se genero una conexion exitosa");
}

void initConnection(){
   
//  wifiManager.resetSettings();
  
  connection();
}

void resetConfiguration(){
  wifiManager.resetSettings();
  connection();
}
