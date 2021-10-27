#ifndef WiFiNetwork_h
#define WiFiNetwork_h

enum class ConnectionStatus { OK, WRONG_SSID, WRONG_PASS, TIMEOUT };

class WiFiNetwork {
  private:
    const static int DEFAULT_RETRY_TIMEOUT_MS = 1000;

    const char *ssid;
    const char *pass;
    int retry_timeout_ms;

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
};

#endif
