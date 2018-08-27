#ifndef __SSD_1309_H__
#define __SSD_1309_H__

#include <Arduino.h>
#include <SPI.h>
#include "fonts.h"

class Ssd1309 {
	public :
		Ssd1309(uint8_t chipSelectPin, uint8_t readWritePin, uint8_t resetPin);
		void init();
		void clearBuffer();
		void pixel(uint8_t x, uint8_t y);
		void line(uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2);
		void print(uint8_t x, uint8_t y, char* str);
		void display();

	private :
		char buffer[1024];
		SPISettings setting;
		uint8_t cs, rw, rs;
		void sendCommand(uint8_t cmd);
		void sendCommand(uint8_t cmd, uint8_t value);
};

#endif
