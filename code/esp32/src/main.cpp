#include <Arduino.h>
#include "fileHandler.h"
#include "connectionHandler.h"
#include "buttonHandler.h"

void setup()
{
	Serial.begin(115200);

	FileHandler.init();
	FileHandler.loadConnectionHandlerSettings();
	ConnectionHandler.init();
  ButtonHandler.init();
}

const long interval = 100;		   // interval at which to blink (milliseconds)
unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval2 = 1000;	   // interval at which to blink (milliseconds)
unsigned long previousMillis2 = 0; // will store last time LED was updated

void loop()
{
	unsigned long currentMillis = millis();
	ConnectionHandler.wifiConnecAsync();

	if (ConnectionHandler.wifiConnected())
	{
		ConnectionHandler.mqttConnect();
		if (ConnectionHandler.mqttConnected())
		{
			if (ConnectionHandler.sendTopic == ConnectionHandler.setupSend)
				{
					ButtonHandler.systemState = ButtonHandler.systemSetup;
				}
			else 
			{
				ButtonHandler.systemState = ButtonHandler.systemOperating;
			}
			switch (ButtonHandler.systemState)
			{
			case ButtonHandler.systemOperating:
				if (ButtonHandler.btnChecker())
				{
					if (currentMillis - previousMillis2 >= interval2)
					{
						previousMillis2 = currentMillis;
            			Serial.println("Sending mqtt message");
						ConnectionHandler.sendMQTT();
					}
          			Serial.println("Updating LEDs");
					ButtonHandler.LEDUpdate();
				}
				break;
			case ButtonHandler.systemSetup:
				ButtonHandler.btnSetup();
				break;
			}
		}
	}
}