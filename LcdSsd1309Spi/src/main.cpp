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

uint8_t smilley[8] = {
	0b01111110,
	0b10000001,
	0b10100101,
	0b10000001,
	0b10100101,
	0b10011001,
	0b10000001,
	0b01111110
};

uint8_t cross[8] = {
	0b10000000,
	0b01000000,
	0b00100000,
	0b00010000,
	0b00001000,
	0b00000100,
	0b00000010,
	0b00000001
};

void setup() {
	lcd.init();
}
uint8_t data = 0x00;

int x=1;
int y=1;
int dx = 2;
int dy = 2;

void loop() {

	lcd.clearBuffer();
	lcd.print(2,2, "Bonjour!");

	lcd.hline(x-1,x+1, y-1);
	lcd.hline(x-1,x+1, y);
	lcd.hline(x-1,x+1, y+1);

	lcd.hline(0, 127, 0);
	lcd.hline(0, 127, 63);
	lcd.vline(0, 0, 63);
	lcd.vline(127, 0, 63);

	lcd.line(10,20,120,50);
	lcd.line(20,15,40,55);

	lcd.sprite(90,15,8,8,smilley);
	lcd.sprite(100,25,8,8,cross);

	lcd.display();

	x+=dx;
	y+=dy;
	if (x>=125) dx=-1;
	if (x<=2) dx=1;
	if (y>=61) dy=-1;
	if (y<=2) dy = 1;
}
