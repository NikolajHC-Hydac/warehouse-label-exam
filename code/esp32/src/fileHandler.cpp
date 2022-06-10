#include <Arduino.h>
#include "fileHandler.h"
#include "LITTLEFS.h"
#include <ArduinoJson.h>
#include "connectionHandler.h"

FileHandlerClass FileHandler;

void FileHandlerClass::init()
{
	Serial.println("Initializing littleFS..");
	if (!LittleFS.begin())
	{
		Serial.println("An Error has occurred while mounting LittleFS");
		return;
	}
}

void FileHandlerClass::loadConnectionHandlerSettings()
{
	StaticJsonDocument<500> Doc;

	File file = LittleFS.open("/settings.json", "r");
	if (!file)
	{
		Serial.println("Failed to open settings file for reading");
		return;
	}
	char line[500];
	memset(line, 0, sizeof(line));
	int i = 0;
	while (file.available() && i < sizeof(line))
	{
		line[i] = file.read();
		i++;
	}

	DeserializationError error = deserializeJson(Doc, line);
	if (error)
	{
		Serial.print(F("deserializeJson() failed: "));
		Serial.println(error.f_str());
	}
	else
	{
		//ConnectionHandler.settings.SSID = Doc["ssid"].as<const char *>();
		//ConnectionHandler.settings.WiFiPassword = Doc["password"].as<const char *>();
		ConnectionHandler.settings.MQTTBroker = Doc["mqtt_broker"].as<String>();
		ConnectionHandler.settings.MQTTPort = Doc["mqtt_port"].as<int>();
		ConnectionHandler.settings.MQTTUsername = Doc["mqtt_username"].as<String>();
		ConnectionHandler.settings.MQTTPassword = Doc["mqtt_password"].as<String>();
	}
	file.close();
}
