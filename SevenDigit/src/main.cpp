#include <Arduino.h>

// Broche connectée au ST_CP du 74HC595
const int verrou = 11;
// Broche connectée au SH_CP du 74HC595
const int horloge = 12;
// Broche connectée au DS du 74HC595
const int data = 10;

const char numbers[] = {
	0b01111110,
	0b01011011,
	0b01100000,
	0b01110011,
	0b01100101,
	0b00110111,
	0b00111111,
	0b01100010,
	0b01111111,
	0b01110111
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
