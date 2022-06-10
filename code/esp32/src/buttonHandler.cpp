#include <Arduino.h>
#include "buttonHandler.h"

ButtonHandlerClass ButtonHandler;

void ButtonHandlerClass::init()
{
	ow = new OneWireNg_CurrentPlatform(OW_PIN, false);
	delay(3000); // 3 second delay for recovery
	// tell FastLED about the LED strip configuration
	FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(BRIGHTNESS); // Set master brightness control
	FastLED.clear();
	FastLED.show();
}

void ButtonHandlerClass::btnSetup()
{
	int dot = 0;
	leds[dot] = CRGB::Blue;
	FastLED.show();
	while (dot < NUM_LEDS)
	{
		if (btnChecker() == 1)
		{
			leds[dot] = CRGB::Black;
			dot++;
			leds[dot] = CRGB::Blue;
			FastLED.show();
		}
	}
}

void ButtonHandlerClass::printId(const OneWireNg::Id &id)
{
	Serial.print(id[0], HEX);
	String tButtonSN;
	for (size_t i = 1; i < sizeof(OneWireNg::Id); i++)
	{
		Serial.print(':');
		Serial.print(id[i], HEX);
		tButtonSN = +id[i];
	}
	Serial.println();
	String buttonSN = tButtonSN;
}

bool ButtonHandlerClass::btnChecker()
{
	unsigned char state = btnSearch();
	if (state != LastState && state != 0)
	{ // Check to see if a button has been pressed since last time a button was pressed
		LastState = state;
		return 1;
	}
	LastState = state;
	return 0;
}

unsigned char ButtonHandlerClass::btnSearch()
{
	OneWireNg::Id id;
	ow->searchReset();
	while (ow->search(id) == OneWireNg::EC_MORE)
	{
		Serial.println("Found buttons");
		printId(id);
		// Add button state to map, and create iterator for finding id
		std::map<OneWireNg::Id, btnState_s>::iterator it = buttonStates.find(id);
		if (it != buttonStates.end())
		{ // If id is found
			if (it->second.btnState <= 1) // If state is less than or equal to 1
			{							
				it->second.btnState++;
				buttonSN = ow->search(id);
			}
			else
			{
				Serial.println("button exists, state is max");
			}
		}
		return 1;
	}
	return 0;
}

void ButtonHandlerClass::LEDUpdate()
{
	int i = 0;
	for (auto iter = buttonStates.begin(); iter != buttonStates.end(); ++iter)
	{
		if (iter->second.btnState == 0)
		{
			leds[iter->second.ledIndex] = CRGB::Black;
		}
		else if (iter->second.btnState == 1)
		{
			leds[iter->second.ledIndex] = CRGB::Yellow;
		}
		else
		{
			leds[iter->second.ledIndex] = CRGB::Red;
		}
		i++;
	}
	FastLED.show();
	delay(30);
}
