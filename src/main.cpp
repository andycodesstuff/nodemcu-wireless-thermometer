#include "env.h"
#include "net/wifi_network.h"
#include "sensors/thermistor.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>

Thermistor thermistor(A0, 1024);
WiFiNetwork network(WIFI_SSID, WIFI_PASSPHRASE);

void setup() {
  Serial.begin(115200);
  delay(10);

  network.connect(30000);
}

void loop() {
  double temp_C = thermistor.get_temperature_C();

  Serial.print("T: ");
  Serial.println(temp_C);
  delay(1000);
}
