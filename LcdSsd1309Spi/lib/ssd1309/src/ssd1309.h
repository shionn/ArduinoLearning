#ifndef __SSD_1309_H__
#define __SSD_1309_H__

#include <Arduino.h>
#include <SPI.h>

class Ssd1309 {
	public :
		Ssd1309(uint8_t chipSelectPin, uint8_t readWritePin, uint8_t resetPin);
		void init();
		void clearBuffer();
		void display();


	public :
		char buffer[1024];
		SPISettings setting;
		uint8_t cs, rw, rs;
		void sendCommand(uint8_t cmd);
		void sendCommand(uint8_t cmd, uint8_t value);
};

#endif
