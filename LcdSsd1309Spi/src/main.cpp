#include <Arduino.h>
#include <SPI.h>

// CS ou SS ou CHIP SELECT : RS
#define CS 10
// DS
#define RW 9
// DATA ou MOSI ou SDA : R/W
#define DATA 11
// CLOCK, E, SCL
#define CLOCK 13



SPISettings setting = SPISettings(10000, MSBFIRST, SPI_MODE0); // max 4000000

void sendCommand(uint8_t data) {
	digitalWrite(RW, LOW);
	digitalWrite(CS, LOW);
	SPI.transfer(data);
	digitalWrite(CS, HIGH);
}

void setup() {
	pinMode(CS, OUTPUT);
	pinMode(RW, OUTPUT);
	digitalWrite(CS, HIGH);

	SPI.begin();
	SPI.beginTransaction(setting);
	sendCommand(0xA5); // display on
	sendCommand(0xAF); // display on
	//sendCommand(0xD5);
	sendCommand(0x81); // contrast
	sendCommand(0x7F); // contrast value
	sendCommand(0xA4); // ram to display ?

	sendCommand(0x2A);
	//sendCommand(0x01);
	sendCommand(0x2F);

	SPI.endTransaction();
}
uint8_t data = 0;

void loop() {
	delay(10);
	SPI.beginTransaction(setting);
	digitalWrite(RW, HIGH);
	digitalWrite(CS, LOW);
	SPI.transfer(random(255));
	digitalWrite(CS, HIGH);
	SPI.endTransaction();
}
