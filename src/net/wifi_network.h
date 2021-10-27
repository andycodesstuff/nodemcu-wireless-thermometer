#ifndef WiFiNetwork_h
#define WiFiNetwork_h

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

enum class ConnectionStatus { OK, WRONG_SSID, WRONG_PASS, TIMEOUT };

class WiFiNetwork {
  private:
    const static int DEFAULT_RETRY_TIMEOUT_MS = 1000;
    const static int REMOTE_UDP_PORT = 13337;

    const char *ssid;
    const char *pass;
    int retry_timeout_ms;
    bool is_connected;
    WiFiUDP udp;

    /**
     * Compute the broadcast address of the connected network. If it is not connected to a network,
     * returns the IPv4 address 255.255.255.255
     */
    IPAddress __compute_broadcast_address();

  public:
    /**
     * Constructor.
     * 
     * @param _ssid The name of the WiFi
     * @param _pass The passphrase for the WiFi
     */
    WiFiNetwork(const char *_ssid, const char *_pass, int _retry_timeout_ms = WiFiNetwork::DEFAULT_RETRY_TIMEOUT_MS);

    /**
     * Attempt to connect to the WiFi network.
     * 
     * @param timeout_ms The time to wait before forcefully interrupting connection attempt
     */
    ConnectionStatus connect(int timeout_ms);

    /**
     * Send a broadcast message to the connected network.
     * 
     * @param msg The message to send
     */
    void send(const char *msg);
};

#endif
