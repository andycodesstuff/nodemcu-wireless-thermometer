#include "wifi_network.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>

WiFiNetwork::WiFiNetwork(const char *_ssid, const char *_pass, int _retry_timeout_ms) {
  WiFiNetwork::ssid = _ssid;
  WiFiNetwork::pass = _pass;
  WiFiNetwork::retry_timeout_ms = _retry_timeout_ms;
}

ConnectionStatus WiFiNetwork::connect(int timeout_ms) {
  wl_status_t current_status;
  int current_retries = 0,
      max_retries = timeout_ms / WiFiNetwork::retry_timeout_ms;

  // Attempt to connect to the network
  WiFi.begin(WiFiNetwork::ssid, WiFiNetwork::pass);
  Serial.print("connecting to \"");
  Serial.print(ssid);
  Serial.println("\"...");

  // Wait until connection is established or timeout is exceeded
  while ((current_status = WiFi.status()) == WL_DISCONNECTED && (current_retries * WiFiNetwork::retry_timeout_ms) < timeout_ms) {
    current_retries++;

    Serial.print("connection attempt ");
    Serial.print(current_retries);
    Serial.print("/");
    Serial.print(max_retries);
    Serial.print(" (status: ");
    Serial.print(current_status);
    Serial.println(")");

    delay(WiFiNetwork::retry_timeout_ms);
  }

  // Timeout exceeded
  if (current_retries == max_retries) {
    return ConnectionStatus::TIMEOUT;
  }

  switch (current_status) {
    case WL_NO_SSID_AVAIL:
      Serial.print("SSID \"");
      Serial.print(ssid);
      Serial.println("\" is not available");
      return ConnectionStatus::WRONG_SSID;
    case WL_WRONG_PASSWORD:
      Serial.print("wrong passphrase for SSID \"");
      Serial.print(ssid);
      Serial.println("\"");
      return ConnectionStatus::WRONG_PASS;
    case WL_CONNECTED:
      Serial.print("connection established (IPv4 address: ");
      Serial.print(WiFi.localIP());
      Serial.println(")");
      return ConnectionStatus::OK;
    default:
      return ConnectionStatus::TIMEOUT;
  }
}
