# neopixel test

## Test build
To test neopixels for addressing LED's, the following breadboard was build:  
![Breadboard with neopixels test.](https://github.com/HydacDK/New-Warehouse-Lables/blob/Prototype4/images/neopixel_breadboard.jpg)
Ten ws2812b LED's were connected in series, with small decoupling capacitors connected between each LED's VDD and ground, as well as a large capacitor connected across the + and - terminals of the DC power supply.  
![Circuit diagram showing the resistor ladder test setup](https://github.com/HydacDK/New-Warehouse-Lables/blob/Prototype4/images/neopixel_circuit.jpg)

## Test code
The FastLED library was used along with some slightly modified example code to test the neopixels functionality, and to gain familiarity with how they function.  
[See code here](https://github.com/HydacDK/New-Warehouse-Lables/blob/Prototype4/code/tests/Neopixel/src/main.cpp)

## Observations

 - The adafruit_neopixel library was incomplatible with the at the time current version of arduino being used with platformIO. This may be fixed with the newest version of the espressif 32 platform as it has been updated to include arduino 2.0
 - It is easy to address individual LED's with neopixels
 - Wiring is minimal. Aditional components needed is also very small

## Conclusion
Using neopixels for addressing LED's seems like a good fit for the project:

 - Positives:
	 - Cheap
	 - Easy to use
	 - Abundant worldwide stock
	 - Minimal wiring needed
	 - Few components to make work
- Cons:
	- LED's will not have same serial as their respective buttons
	- Will require some setup on first run.

Using neopixels for addressing LED's would significantly cut down on the amount of cables needed compared to charlieplexing, and make the system easily scaleable, with minimal setup required at the start of use.
