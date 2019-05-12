const char* ssid = "der-palmenhain";
const char* password = "bonjourstuttgart";

const int NB_HUE_DEVICES = 2;

const char* ip_hue = "192.168.1.2";
const char* ip_pi = "192.168.1.4";
const char* dev_id_hue = "fRkcEAkfYx6CkGjl0FDmTzttW-sD9LPFyX9syBRj";
const char* dev_id_pi = "250d44730930779ddb63a39fb61f1b41";

String address_hue = String("http://" + String(ip_hue) + "/api/" + String(dev_id_hue) + "/lights");
String address_pi = String("http://" + String(ip_pi) + "/api/" + String(dev_id_pi) + "/lights");

String my_addresses[NB_HUE_DEVICES];
