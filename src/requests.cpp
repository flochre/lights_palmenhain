#include "requests.h"

int get_request(HTTPClient *my_http, String my_request){
  // http.begin("http://192.168.1.2/api/fRkcEAkfYx6CkGjl0FDmTzttW-sD9LPFyX9syBRj/lights/");
  my_http->begin(my_request);
  my_http->addHeader("Content-Type", "text/plain");
  return my_http->GET();
}

int put_request(HTTPClient *my_http, String my_request, String body){
  my_http->begin(my_request);
  my_http->addHeader("Content-Type", "text/plain");
  return my_http->sendRequest("PUT", body.c_str());
}
