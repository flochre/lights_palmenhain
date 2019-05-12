#include <Arduino.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#include "config.h"
#include "requests.h"


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
  if(WiFi.status()== WL_CONNECTED){
    // We are connected to the Wifi

    HTTPClient http;

    String address_hue = String("http://" + String(ip_hue) + "/api/" + String(dev_id_hue) + "/lights");
    String address_pi = String("http://" + String(ip_pi) + "/api/" + String(dev_id_pi) + "/lights");
    int httpResponseCode = get_request(&http, address_pi);

   // String data = "{\"on\":true}";
   // int httpResponseCode = http.sendRequest("PUT", data.c_str());

    if(httpResponseCode>0){

      String response = http.getString();

      Serial.println(httpResponseCode);
      Serial.println(response);

    } else {

      Serial.print("Error on sending PUT Request: ");
      Serial.println(httpResponseCode);

    }

    http.end();

  } else {
    Serial.println("Error in WiFi connection");
  }

  delay(10000);
}
