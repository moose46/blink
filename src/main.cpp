/*
  SparkFun Electronics 2013
  Playing with Infrared Remote Control

  IR Receiver Breakout (SEN-8554): Supply voltage of 2.5V to 5.5V
	Attach
	OUT: To pin 11 on Arduino
	GND: GND
	VCC: 5V

  This is based on Ken Shirriff's code found on GitHub:
  https://github.com/shirriff/Arduino-IRremote/

  This code works with cheap remotes. If you want to look at the individual timing
  of the bits, use this code:
  http://www.arduino.cc/playground/Code/InfraredReceivers
*/
#include<Arduino.h>
#include <IRremote.h>
#include <blink.h>
decode_results results;
IRrecv irrecv(RECV_PIN);

bool on_off = false;
bool blink_on_off = false;

void blink_it();
void isr_state_change()
{
	Serial.println("How Low can you go?");
}
void setup()
{
	Serial.begin(9600);
	irrecv.enableIRIn(); // Start the receiver
	Serial.println("Hello World\n");
	pinMode(LED, OUTPUT);
}

void loop()
{
	if (irrecv.decode(&results))
	{
		if (results.value == SONY_TV_POWER)
		{
			if (on_off) {
				on_off = false;
				digitalWrite(LED, LOW);
				Serial.println("\nLamp off!");
			}
			else {
				on_off = true;
				digitalWrite(LED, HIGH);
				Serial.println("\nLamp on!");
			}

			Serial.println("POWER");
		}
		if (results.value == SONY_TV_PLAY)
		{
			blink_on_off = true;
			blink_it();
			Serial.println("Back from blink_it()");
		}
		if (results.value == SONY_TV_PAUSE)
		{
			blink_on_off = false;
			Serial.println("NO BLINK");
		}

		Serial.println(results.value, HEX);
		delay(600);
		irrecv.resume();
	}
	
}

