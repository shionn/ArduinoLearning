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

	lcd.clearBuffer();
	lcd.print(0,0, "Bonjour !");
	lcd.pixel(x, y);
	lcd.line(0,63,127, 63);
	lcd.line(10,20,120,50);
	lcd.line(20,10,40,50);
	lcd.line(50,20,120,20);
	lcd.line(5,15,5,60);
	lcd.display();

	x+=dx;
	y+=dy;
	if (x>=127) dx=-1;
	if (x<=0) dx=1;
	if (y>=63) dy=-1;
	if (y<=0) dy = 1;
}
