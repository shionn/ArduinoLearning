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
// Reset, RS
#define RS 8



SPISettings setting = SPISettings(4000000UL, MSBFIRST, SPI_MODE0); // max 4000000

void sendCommand(uint8_t data) {
	digitalWrite(RW, LOW);
	digitalWrite(CS, LOW);
	SPI.transfer(data);
	digitalWrite(CS, HIGH);
}

void sendCommand(uint8_t data, uint8_t value) {
	digitalWrite(RW, LOW);
	digitalWrite(CS, LOW);
	SPI.transfer(data);
	SPI.transfer(value);
	digitalWrite(CS, HIGH);
}

void setup() {
	pinMode(RS, OUTPUT);
	pinMode(CS, OUTPUT);
	pinMode(RW, OUTPUT);

	digitalWrite(CS, LOW);
	digitalWrite(RS, HIGH);
	digitalWrite(RS, LOW);
	delay(40);
	digitalWrite(RS, HIGH);
	digitalWrite(CS, HIGH);

	SPI.begin();
	SPI.beginTransaction(setting);
//	sendCommand(0xA4); // display on/off ?
//	sendCommand(0xA5); // display on/off ?
	sendCommand(0xAE); // display off
	sendCommand(0xD5, 0x80); // display clock
	sendCommand(0xA8, 0x3F); // Multiplex ratio
	sendCommand(0xD3, 0x00); // display offset
	sendCommand(0x40); // display start line
	sendCommand(0x8D,0x10|0x04 ); // charge pump
	sendCommand(0x20,0x02); // memory acces mode (00 : horizontal, 01 vertical, 02 page)
	sendCommand(0xA0 || 0x01); // segment remap (00 : 0 to seg0, 01 : 0 to seg 127)
	sendCommand(0xC0 || 0x08);// output scan directory (00 : 0 to 63, 08 : 63 to 00)
	sendCommand(0xDA, 0x12); // Common HW coinfig ?
	sendCommand(0x81,0xCF); // contrast
	sendCommand(0xD9,0xF1); // pre charge period (resou le probleme de pixel mal allumé)
	sendCommand(0xDB,0x40); // VCom lvl commande ?
	sendCommand(0xA4 | 0x00); // entire display on (00 : normal, 01 : entire on)
	sendCommand(0xA6 | 0x00); // Inverted_Display (00 : normal, 01 : inverted)
	sendCommand(0xAF); // display on
	SPI.endTransaction();
}
uint8_t data = 0;

void loop() {
	SPI.beginTransaction(setting);
	sendCommand(0xB0); // page 0
	sendCommand(0x00); // lower column start
	sendCommand(0x10); // high column start
	digitalWrite(RW, HIGH);
	digitalWrite(CS, LOW);
	for (int i=0;i<128;i++)
		SPI.transfer(0x0F);
	digitalWrite(CS, HIGH);

	sendCommand(0xB0+0x01); // page 1
	sendCommand(0x00); // lower column start
	sendCommand(0x10); // high column start
	digitalWrite(RW, HIGH);
	digitalWrite(CS, LOW);
	for (int i=0;i<128;i++)
		SPI.transfer(0xAA);
	digitalWrite(CS, HIGH);
	SPI.endTransaction();
}
