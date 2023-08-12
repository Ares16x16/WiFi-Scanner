#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "";
const char* password = "";
const char* udpAddress = "192.168.1.48";
const int udpPort = 8000; 
int counter = 1;
int delayTime = 700; // Minimum 700
WiFiUDP udpClient;

void setup() {
    Serial.begin(115200);

    Serial.printf("Connecting to %s\n", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    Serial.print("UDP client IP address: ");
    Serial.println(WiFi.localIP());

    Serial.printf("Scanning WiFi networks, Number of trial: %d\n", counter);
    int n = WiFi.scanNetworks();

    String message = "";
    for (int i = 0; i < n; i++) {
        String ssid = WiFi.SSID(i);
        int rssi = WiFi.RSSI(i);
        int channel = WiFi.channel(i);
        String encryption;
        switch (WiFi.encryptionType(i)){
            case WIFI_AUTH_OPEN:
                encryption = "open";
                break;
            case WIFI_AUTH_WEP:
                encryption = "WEP";
                break;
            case WIFI_AUTH_WPA_PSK:
                encryption = "WPA";
                break;
            case WIFI_AUTH_WPA2_PSK:
                encryption = "WPA2";
                break;
            case WIFI_AUTH_WPA_WPA2_PSK:
                encryption = "WPA+WPA2";
                break;
            case WIFI_AUTH_WPA2_ENTERPRISE:
                encryption = "WPA2-EAP";
                break;
            case WIFI_AUTH_WPA3_PSK:
                encryption = "WPA3";
                break;
            case WIFI_AUTH_WPA2_WPA3_PSK:
                encryption = "WPA2+WPA3";
                break;
            case WIFI_AUTH_WAPI_PSK:
                encryption = "WAPI";
                break;
            default:
                encryption = "unknown";
        }

        message += ssid + "$" + String(rssi) + "$" + String(channel) + "$" + encryption + "\n";
    }

    udpClient.beginPacket(udpAddress, udpPort);
    udpClient.print(message);
    udpClient.endPacket();
    Serial.println("Finished sending"); 
    counter++;
    delay(500);
}

void loop() {
    Serial.printf("Scanning WiFi networks, Number of trial: %d\n", counter);
    int n = WiFi.scanNetworks();

    String message = "";
    for (int i = 0; i < n; i++) {
        String ssid = WiFi.SSID(i);
        int rssi = WiFi.RSSI(i);
        int channel = WiFi.channel(i);
        String encryption;
        switch (WiFi.encryptionType(i)){
            case WIFI_AUTH_OPEN:
                encryption = "open";
                break;
            case WIFI_AUTH_WEP:
                encryption = "WEP";
                break;
            case WIFI_AUTH_WPA_PSK:
                encryption = "WPA";
                break;
            case WIFI_AUTH_WPA2_PSK:
                encryption = "WPA2";
                break;
            case WIFI_AUTH_WPA_WPA2_PSK:
                encryption = "WPA+WPA2";
                break;
            case WIFI_AUTH_WPA2_ENTERPRISE:
                encryption = "WPA2-EAP";
                break;
            case WIFI_AUTH_WPA3_PSK:
                encryption = "WPA3";
                break;
            case WIFI_AUTH_WPA2_WPA3_PSK:
                encryption = "WPA2+WPA3";
                break;
            case WIFI_AUTH_WAPI_PSK:
                encryption = "WAPI";
                break;
            default:
                encryption = "unknown";
        }

        message += ssid + "$" + String(rssi) + "$" + String(channel) + "$" + encryption + "\n";
    }

    udpClient.beginPacket(udpAddress, udpPort);
    udpClient.print(message);
    udpClient.endPacket();
    Serial.println("Finished sending"); 
    counter++;
    delay(500);
}
