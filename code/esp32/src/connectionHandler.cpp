#include <Arduino.h>

#include <WiFi.h> // Go through code and update wifi stuff
#include "connectionHandler.h"
#include "PubSubClient.h"
#include "buttonHandler.h"
#include <string>

ConnectionHandlerClass ConnectionHandler;
WiFiClient espClient;
PubSubClient client(espClient);

void ConnectionHandlerClass::init()
{
    pinMode(WiFiLED, OUTPUT);
    pinMode(MQTTLED, OUTPUT);
    int numSsid = WiFi.scanNetworks();
    if (numSsid == -1) {
      Serial.println("Couldn't get a wifi connection");
      while (true);
    }

    // print the list of networks seen:
    Serial.print("number of available networks:");
    Serial.println(numSsid);

    // print the network number and name for each network found:
    for (int thisNet = 0; thisNet < numSsid; thisNet++) {
      Serial.print(thisNet);
      Serial.print(") ");
      Serial.print(WiFi.SSID(thisNet));
      Serial.print("\tSignal: ");
      Serial.print(WiFi.RSSI(thisNet));
      Serial.print(" dBm");
    }
}

void ConnectionHandlerClass::wifiConnecAsync()
{
    uint32_t ts = millis();
    if (ts > (wifiLastAttempt + wifiReconnect_interval) || wifiLastAttempt == 0)
    {
        wifiLastAttempt = ts;

        switch (wifiConnectionState)
        {
        case WifiNotConnected:
            // connect to the network
            WiFi.begin(settings.SSID, settings.WiFiPassword);
            wifiReconnect_interval = 200;
            wifiConnectionState = WifiConnecting;
            break;
        case WifiConnecting:
            // Wait for connection
            if (WiFi.status() == WL_CONNECTED)
            {
                wifiReconnect_interval = 10000;
                wifiConnectionState = WifiConnected;
                Serial.println("\nConnected to WiFi.");
            }

            Serial.print(".");
            wifiSubAttempts++;
            if (wifiSubAttempts >= 50)
            {
                // We have waited for a long time, send an error and try again
                Serial.println();
                wifiAttempt++;
                wifiSubAttempts = 0;
                Serial.printf("Failed to connect to WiFi on attempt: %d.\n\n", wifiAttempt);
                Serial.println("to SSID: " + String(settings.SSID) + " with pass: " + String(settings.WiFiPassword));
                wifiConnectionState = WifiNotConnected;
            }
            break;
        case WifiConnected:
            // All good, check that we have not been disconnected
            if (WiFi.status() != WL_CONNECTED)
            {
                wifiReconnect_interval = 200;
                wifiConnectionLosses++;
                wifiConnectionState = WifiNotConnected;
                wifiAttempt = 0;
                Serial.println("Disconnected from WiFi.");
                Serial.printf("Connection status: %d\n", WiFi.status());
                digitalWrite(WiFiLED, LOW);
            }
            digitalWrite(WiFiLED, HIGH);
            break;
        default:
            wifiReconnect_interval = 200;
            wifiConnectionState = WifiNotConnected;

            break;
        }
    }
}

bool ConnectionHandlerClass::wifiConnected()
{
    return wifiConnectionState == WifiConnected;
    Serial.println(macAdd);
}
void ConnectionHandlerClass::callback(char *topic, uint8_t *payload, unsigned int length)
{
    if ((char)payload[0] == '1')
    {
        sendTopic = setupSend;
    }
    else
    {
        sendTopic = order;
    }
}
void ConnectionHandlerClass::mqttConnect()
{
    client.setServer(settings.MQTTBroker.c_str(), settings.MQTTPort);
    client.setCallback(std::bind(&ConnectionHandlerClass::callback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    client.setKeepAlive(60);
    client.setSocketTimeout(30);
    uint32_t ts = millis();
    if (ts > (mqttLastAttempt + mqttReconnect_interval) || mqttLastAttempt == 0)
    {
        mqttLastAttempt = ts;

        switch (mqttConnectionState)
        {
        case MqttNotConnected:
            // connect to the MQTT broker
            Serial.print("Broker ");
            Serial.println(settings.MQTTBroker.c_str());
            Serial.print("Port ");
            Serial.println(settings.MQTTPort);
            Serial.print("Client Id ");
            Serial.println(clientId.c_str());
            client.connect(clientId.c_str(), settings.MQTTUsername.c_str(), settings.MQTTPassword.c_str());
            mqttReconnect_interval = 200;
            mqttConnectionState = MqttConnecting;
            break;
        case MqttConnecting:
            // Wait for connection
            if (client.connected() == true)
            {
                mqttReconnect_interval = 10000;
                mqttConnectionState = MqttConnected;
                Serial.println("\nConnected to MQTT.");
                client.subscribe(setupReceive.c_str());
            }

            Serial.print(".");
            mqttSubAttempts++;
            if (mqttSubAttempts >= 50)
            {
                // We have waited for a long time, send an error and try again
                Serial.println();
                mqttAttempt++;
                mqttSubAttempts = 0;
                Serial.printf("Failed to connect to MQTT broker on attempt: %d.\n\n", mqttAttempt);
                Serial.println("");
                Serial.println("MQTT state:" + String(client.state()));
                mqttConnectionState = MqttNotConnected;
            }
            break;
        case MqttConnected:
            // All good, check that we have not been disconnected
            if (client.state() != 0)
            {
                mqttReconnect_interval = 200;
                mqttConnectionLosses++;
                mqttConnectionState = MqttNotConnected;
                mqttAttempt = 0;
                Serial.printf("Disconnected from MQTT broker. Returns client state: %d.\n\n", client.state());
                digitalWrite(MQTTLED, LOW);
            }
            digitalWrite(MQTTLED, HIGH);
            client.loop();
            break;
        default:
            mqttReconnect_interval = 200;
            mqttConnectionState = MqttNotConnected;

            break;
        }
    }
}

bool ConnectionHandlerClass::mqttConnected()
{
    return mqttConnectionState == MqttConnected;
}

void ConnectionHandlerClass::sendMQTT()
{
    if (ButtonHandler.btnChecker() != 0)
    {
        String messageConstruct = ButtonHandler.buttonSN + " " + macAdd;
        client.publish(sendTopic.c_str(), messageConstruct.c_str());
    }
}