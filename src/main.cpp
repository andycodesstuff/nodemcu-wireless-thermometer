#include "env.h"
#include "net/wifi_network.h"
#include "sensors/thermistor.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define NTP_ADDRESS "europe.pool.ntp.org"
#define NTP_INTERVAL_MS 60 * 1000
#define NTP_OFFSET_S 2 * 60 * 60

Thermistor thermistor(A0, 1024);
WiFiNetwork network(WIFI_SSID, WIFI_PASSPHRASE);
WiFiUDP ntpUDP;
NTPClient ntpClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET_S, NTP_INTERVAL_MS);

void setup() {
  Serial.begin(115200);
  delay(10);

  network.connect(30000);
  ntpClient.begin();
}

void loop() {
  ntpClient.update();

  // Get temperature reading and epoch timestamp
  double temp_C = thermistor.get_temperature_C();
  unsigned long epoch = ntpClient.getEpochTime();

  // Construct JSON message
  String msg = String("{ \"ts\": ") +
               String(epoch) +
               String(", \"t\": ") +
               String(temp_C) +
               String(" }");
  network.send(msg.c_str());
  Serial.println(msg);

  delay(1000);
}
