# Onewire test

## Test build
To test using the onewire protocol for button identification, the following breadboard was build:  
![Breadboard with onewire test setup, as seen from the side.](https://github.com/HydacDK/New-Warehouse-Lables/blob/Prototype4/images/onewire_breadboard_side.jpg)
![Breadboard with onewire test setup, as seen from the top.](https://github.com/HydacDK/New-Warehouse-Lables/blob/Prototype4/images/onewire_breadboard_top.jpg)
four DS2413 onewire units were connected in series with  each other. These onewire units were connected to GND through a momentary button, only powering them on when the button was being held.  
![Circuit diagram showing the onewire ladder test setup](https://github.com/HydacDK/New-Warehouse-Lables/blob/Prototype4/images/onewire_circuit.jpg)

## Test code
The following code was written to test the usage of the onewire protocol for button identification:  
    
    #include <Arduino.h>
    #include "OneWireNg_CurrentPlatform.h"

    #define OW_PIN          14

    static OneWireNg *ow = NULL;


    static void printId(const OneWireNg::Id& id) {
        Serial.print(id[0], HEX);
        for (size_t i = 1; i < sizeof(OneWireNg::Id); i++) {
            Serial.print(':');
            Serial.print(id[i], HEX);
        }
        Serial.println();
    }

    void setup() {
        ow = new OneWireNg_CurrentPlatform(OW_PIN, false);
        Serial.begin(115200);
    }

    void loop() {
        OneWireNg::Id id;
        ow->searchReset();
        while (ow->search(id) == OneWireNg::EC_MORE) {
            printId(id);
        }
    }

## Observations

 - Each search where a button is found takes ~15 milliseconds
 - Each search where no button is found takes less than a millisecond
 - Wiring is very simple
 - Only signal and gnd wires need to be used, as vcc is only used to pull up the signal wire
 - Can only be used for buttons, not LED's when used in this way

## Conclusion
Using onewire for addressing buttons seems like a good fit for the project:

 - Positives:
	 - Onewire units that can be used in this way can be as cheap as 0,7 euro a piece.
	 - Easy to use
	 - Decent worldwide stock
	 - Minimal wiring needed
	 - Very fast
	 - No slowdown with more units added
	 - Multiple buttons can be pressed at once (no ghosting)
- Cons:
	- Buttons and LED's will have to be controlled seperately
	- Will require some setup on first run.

Using onewire for addressing buttons would significantly cut down on the amount of cables needed compared to charlieplexing, and make the system easily scaleable, with minimal setup required at the start of use.
