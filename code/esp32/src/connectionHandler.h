#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include <Arduino.h>
#include "WiFi.h"
#include <string.h>

class ConnectionHandlerClass
{
public:
	struct SettingsStruct
	{
		const char* SSID = "Dungeons And Data";
		const char* WiFiPassword = "denSammeSomSidst";
		String MQTTBroker;
		int MQTTPort;
		String MQTTUsername;
		String MQTTPassword;
		String MQTTClientId;
	} settings;

	void init();
	void wifiConnecAsync();
	bool wifiConnected();
	void mqttConnect();
	bool mqttConnected();
	void sendMQTT();
	void callback(char *, uint8_t *, unsigned int);
	
	String order = "DKWarehouse/order";
	String setupSend = "DKWarehouse/setup/RX";
	String setupReceive = "DKWarehouse/setup/TX";
	String sendTopic = order;

private:
	uint16_t wifiAttempt = 0;
	uint8_t wifiSubAttempts = 0;
	uint16_t wifiConnectionLosses = 0;
	enum wifi_connection_states
	{
		WifiNotConnected,
		WifiConnecting,
		WifiConnected
	} wifiConnectionState = WifiNotConnected;

	uint16_t wifiReconnect_interval = 200;
	uint32_t wifiLastAttempt = 0;

	int WiFiLED = 37;
	int MQTTLED = 38;

	uint16_t mqttAttempt = 0;
	uint8_t mqttSubAttempts = 0;
	uint16_t mqttConnectionLosses = 0;
	String macAdd = WiFi.macAddress();
	String clientId = "esp32-"; // Tilføj mac address
	enum mqtt_connection_states
	{
		MqttNotConnected,
		MqttConnecting,
		MqttConnected
	} mqttConnectionState = MqttNotConnected;
	uint16_t mqttReconnect_interval;
	uint32_t mqttLastAttempt = 0;

	uint8_t WiFiConnect(const char *nSSID = nullptr, const char *nPassword = nullptr);
	
};

extern ConnectionHandlerClass ConnectionHandler;

#endif
