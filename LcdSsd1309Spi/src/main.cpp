#include <Arduino.h>
#include <ssd1309.h>

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


Ssd1309 lcd = Ssd1309(CS, RW, RS);

void setup() {
	lcd.init();
}
uint8_t data = 0x00;

int x=0;
int y=0;
int dx = 1;
int dy = 1;

void loop() {
/*	SPI.beginTransaction(lcd.setting);
	for (uint8_t page = 0; page<8; page++) {
		lcd.sendCommand(0xB0+page); // page 0
		lcd.sendCommand(0x00); // lower column start
		lcd.sendCommand(0x10); // high column start
		digitalWrite(RW, HIGH);
		digitalWrite(CS, LOW);
		for (int i=0;i<128;i++)
			SPI.transfer(data);
		digitalWrite(CS, HIGH);
	}
	SPI.endTransaction();

	delay(100);//*/

	lcd.clearBuffer();
	lcd.pixel(x, y);
	lcd.display();

	x+=dx;
	y+=dy;
	if (x>=127) dx=-1;
	if (x<=0) dx=1;
	if (y>=63) dy=-1;
	if (y<=0) dy = 1;
	delay(2);
}
