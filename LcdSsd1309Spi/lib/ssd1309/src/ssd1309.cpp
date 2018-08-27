#include "ssd1309.h"

Ssd1309::Ssd1309(uint8_t chipSelectPin, uint8_t readWritePin, uint8_t resetPin) {
	cs = chipSelectPin;
	rw = readWritePin;
	rs = resetPin;
}

void Ssd1309::init() {
	setting = SPISettings(4000000UL, MSBFIRST, SPI_MODE0); // max 4000000

	pinMode(rs, OUTPUT);
	pinMode(cs, OUTPUT);
	pinMode(rw, OUTPUT);

	digitalWrite(cs, LOW);
	digitalWrite(rs, HIGH);
	digitalWrite(rs, LOW);
	delay(40);
	digitalWrite(rs, HIGH);
	digitalWrite(cs, HIGH);

	SPI.begin();
	SPI.beginTransaction(setting);
	this->sendCommand(0xAE); // display off
//	this->sendCommand(0xD5, 0x80); // display clock
//	this->sendCommand(0xA8, 0x3F); // Multiplex ratio
//	this->sendCommand(0xD3, 0x00); // display offset
//	this->sendCommand(0x40); // display start line
//	this->sendCommand(0x8D,0x10|0x04 ); // charge pump
	this->sendCommand(0x20,0x02); // memory acces mode (00 : horizontal, 01 vertical, 02 page)
//	this->sendCommand(0xA0 || 0x01); // segment remap (00 : 0 to seg0, 01 : 0 to seg 127)
//	this->sendCommand(0xC0 || 0x08);// output scan directory (00 : 0 to 63, 08 : 63 to 00)
//	this->sendCommand(0xDA, 0x12); // Common HW coinfig ?
	this->sendCommand(0x81,0xCF); // contrast
//	this->sendCommand(0xD9,0xF1); // pre charge period (resou le probleme de pixel mal allumé)
//	this->sendCommand(0xDB,0x40); // VCom lvl commande ?
//	this->sendCommand(0xA4 | 0x00); // entire display on (00 : normal, 01 : entire on)
//	this->sendCommand(0xA6 | 0x00); // Inverted_Display (00 : normal, 01 : inverted)
	this->sendCommand(0xAF); // display on
	SPI.endTransaction();
}

void Ssd1309::clearBuffer() {
	for (uint8_t i=0;i<1024;i++) {
		buffer[i] = 0x00;
	}
}

void Ssd1309::display() {
	SPI.beginTransaction(setting);
	for (char page = 0;page <16; page++) {
		sendCommand(0xB0+page);
//		sendCommand(0x00); // lower column start
//		sendCommand(0x10); // high column start
		digitalWrite(rw, HIGH);
		digitalWrite(cs, LOW);
	for (char l=0;l<128;l++) {
			SPI.transfer(0x00);
		}
		digitalWrite(cs, HIGH);
	}
	SPI.endTransaction();
}

void Ssd1309::sendCommand(uint8_t data) {
	digitalWrite(rw, LOW);
	digitalWrite(cs, LOW);
	SPI.transfer(data);
	digitalWrite(cs, HIGH);
}

void Ssd1309::sendCommand(uint8_t data, uint8_t value) {
	digitalWrite(rw, LOW);
	digitalWrite(cs, LOW);
	SPI.transfer(data);
	SPI.transfer(value);
	digitalWrite(cs, HIGH);
}
