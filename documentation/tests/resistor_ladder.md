# Resistor ladder test

## Test build
To test using a resistor ladder for button identification, the following breadboard was build:
![Breadboard with resistor ladder test.](https://github.com/HydacDK/New-Warehouse-Lables/blob/Prototype4/images/resistor_ladder_breadboard.jpg)
Seven button were connected in paralel, with equal value resistors in series between each button.
![Circuit diagram showing the resistor ladder test setup](https://github.com/HydacDK/New-Warehouse-Lables/blob/Prototype4/images/resistor_ladder_circuit.png)

## Test code
The following code was written to test the usage of a resistor ladder for button identification:

    #include <Arduino.h>
	
	#define INPUT_PIN A0
	
	const int numReadings = 10;
	const int deviation = 50;
	
	int readButton();
	int oldResult;
	bool buttonState;
	int readings = 0;
	int total = 0;
	int average = 0;
	int readingCheck = 0;
	int oldReadingCheck = 0;
	
	void setup() {
	  Serial.begin(9600);
	  pinMode(INPUT_PIN, INPUT);
	  buttonState = false;
	}
	
	void loop() {
	  int result = readButton();
	  delay(100);
	  if (result != 0 && !buttonState){
	    Serial.print(result);
	    Serial.print(" ");
	    Serial.println(average);
		oldResult = result;
	    buttonState = true;
	  }
	}
	
	int readButton() {
	  readingCheck = analogRead(INPUT_PIN);
	  if (abs(oldReadingCheck - readingCheck) > deviation){
	    for (readings = 0; readings <= numReadings; readings++){
	      total = total + analogRead(INPUT_PIN);
	    }
	    average = total / readings;
	    total = 0;
	    oldReadingCheck = readingCheck;
	    if (average > 900){
	      total = 0;
	      buttonState = false;
	      return 0;
	    }
	    if (average == 0) return 1;
	    if (average < 100) return 2;
	    if (average < 270) return 3;
	    if (average < 433) return 4;
	    if (average < 582) return 5;
	    if (average < 720) return 6;
	    if (average < 900) return 7;
	  }
	}

## Observations

 - The use of one resistor value severely limits the amount of buttons that can reliably be operated
	 - The test setup had a std. deviation on readings of ~23, with an ADC tolerance of 40.96 using 1% resistors
	 - Having multiple values of resistors, with logarithmicly increasing resistances will change the voltage scaling from logarithmic to linear, making adjacent ADC values roughly equidistant. This will allow for a much higher amount of buttons connected at once. It will also make it possible to dynamically calculate the corresponding button for any given reading, rather than hard-coding the values.
- Using a higher current limiting resistor will reduce teh current consumed by the system, but will also reduce the difference between readings of individual buttons
- Values in the code had to be manually adjusted, and hardcoded to factor in the real resistance of the resistors.
- Using the average of 10 readings taken after a button had been pushed down seemed to decrease deviations in the ADC values being read, but not signifficantly.

## Conclusion
Using a resistor ladder for button identification has its positives and negatives:

 - Positives:
	 - Each individual button is cheap to produce
	 - Simple electronics
	 - Simple code
	 - Constant polling
- Cons:
	- Many wasted buttons is possible issue
	- Each button can only be used in specific positions

If the resistor ladder method is to be used, then each button needs to have unique resistor values. This is possible to make, but it will either require hand soldering resistors to each button, or if designed with resistors already soldered on, then PCB panels will have wasted buttons on them that are not usable anywhere else, unless a button breaks.
