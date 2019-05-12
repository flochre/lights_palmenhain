#include <Arduino.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#include <ArduinoJson.h>

#include "config.h"
#include "requests.h"

int address_check = 0;

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

    String my_addresses[NB_HUE_DEVICES];
    my_addresses[0] = address_hue;
    my_addresses[1] = address_pi;

    int httpResponseCode = get_request(&http, my_addresses[address_check]);
    address_check = (address_check + 1) % NB_HUE_DEVICES;

   // String data = "{\"on\":true}";
   // int httpResponseCode = http.sendRequest("PUT", data.c_str());

    if(httpResponseCode>0){

      String response = http.getString();

      // const size_t capacity = 12*JSON_ARRAY_SIZE(2) + 3*JSON_ARRAY_SIZE(3) + 16*JSON_OBJECT_SIZE(2) + 4*JSON_OBJECT_SIZE(3) + 5*JSON_OBJECT_SIZE(4) + 4*JSON_OBJECT_SIZE(5) + 3*JSON_OBJECT_SIZE(11) + 4*JSON_OBJECT_SIZE(13) + 2610;
      const size_t capacity = response.length() * 1.73;
      DynamicJsonDocument doc(capacity);

      DeserializationError error = deserializeJson(doc, response);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
      }

      // JsonObject lamp = doc["4"];
      // JsonObject lamp_state = lamp["state"];
      // bool lamp_state_on = lamp_state["on"].as<bool>();
      // int lamp_state_bri = lamp_state["bri"].as<int>();
      //
      // Serial.println(httpResponseCode);
      // Serial.println(response.length());
      Serial.println(doc.size());

      for (size_t i = 0; i < doc.size(); i++) {
        JsonObject lamp = doc[String(i + 1)];
        JsonObject lamp_state = lamp["state"];
        bool lamp_state_on = lamp_state["on"].as<bool>();
        int lamp_state_bri = lamp_state["bri"].as<int>();

        Serial.print("State:");
        Serial.println(lamp_state_on);
        Serial.print("Brightness:");
        Serial.println(lamp_state_bri);
      }

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
