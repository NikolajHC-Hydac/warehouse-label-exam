#include <Arduino.h>
#include <map>
#include <FastLED.h>
#include "OneWireNg_CurrentPlatform.h"

FASTLED_USING_NAMESPACE

static OneWireNg *ow = NULL;

class ButtonHandlerClass
{
public:
	void init();
	bool btnChecker();
	unsigned char getState();
	unsigned char btnSearch();
	void printId(const OneWireNg::Id &id);
	void LEDUpdate();
	void btnSetup();
	enum system_states
	{
		systemOperating,
		systemSetup
	} systemState = systemOperating;
	String buttonSN;

private:
#define OW_PIN 5
#define DATA_PIN 4
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 1
	CRGB leds[NUM_LEDS];

#define BRIGHTNESS 96
#define FRAMES_PER_SECOND 120

	struct btnState_s
	{
		int btnState;
		int ledIndex;
	};

	unsigned char LastState;
	unsigned int btnPressed = 0;
	unsigned int button[1][1] = {};
	std::map<OneWireNg::Id, btnState_s> buttonStates;
};

extern ButtonHandlerClass ButtonHandler;