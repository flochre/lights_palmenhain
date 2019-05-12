#include <Arduino.h>

#include <ESP8266HTTPClient.h>

int get_request(HTTPClient *my_http, String my_request);
int put_request(HTTPClient *my_http, String my_request, String body);
