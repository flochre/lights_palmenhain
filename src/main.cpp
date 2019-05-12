#include <Arduino.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#include "config.h"

// void get_request(HTTPClient my_http, String my_request){
//   // http.begin("http:/192.168.1.2/api/fRkcEAkfYx6CkGjl0FDmTzttW-sD9LPFyX9syBRj/lights/");
//   my_http.begin(my_request);
//   my_http.addHeader("Content-Type", "text/plain");
//
//   //return my_http;
// }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status()== WL_CONNECTED){

   HTTPClient http;

   // http = get_request(http, "http:/192.168.1.2/api/fRkcEAkfYx6CkGjl0FDmTzttW-sD9LPFyX9syBRj/lights/");
   http.begin("http://192.168.1.2/api/fRkcEAkfYx6CkGjl0FDmTzttW-sD9LPFyX9syBRj/lights/4/state");
   http.addHeader("Content-Type", "application/json");

   String data = "{\"on\":true}";
   int httpResponseCode = http.sendRequest("PUT", data.c_str());

   if(httpResponseCode>0){

    String response = http.getString();

    Serial.println(httpResponseCode);
    Serial.println(response);

   }else{

    Serial.print("Error on sending PUT Request: ");
    Serial.println(httpResponseCode);

   }

   http.end();

 }else{
    Serial.println("Error in WiFi connection");
 }

  delay(10000);
}
