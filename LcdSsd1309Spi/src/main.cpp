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
uint8_t data = 0;

void loop() {
	lcd.clearBuffer();
	lcd.display();
}
