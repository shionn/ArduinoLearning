#include <Arduino.h>

// Broche connectée au ST_CP du 74HC595
const int verrou = 11;
// Broche connectée au SH_CP du 74HC595
const int horloge = 12;
// Broche connectée au DS du 74HC595
const int data = 10;

const char numbers[] = {
	0b11111100,
	0b10110110,
	0b11000000,
	0b11100110,
	0b11001010,
	0b01101110,
	0b01111110,
	0b11000100,
	0b11111110,
	0b11101110
};


void setup() {
	pinMode(verrou, OUTPUT);
	pinMode(horloge, OUTPUT);
	pinMode(data, OUTPUT);
	digitalWrite(verrou, HIGH);
}


void printNumber(int number) {
	digitalWrite(verrou, LOW);
	shiftOut(data, horloge, LSBFIRST, numbers[number]);
	digitalWrite(verrou, HIGH);
}

int number = 0;
void loop() {

	printNumber(number);
	delay(1000);
	if (number++==9) number = 0; ;

}
