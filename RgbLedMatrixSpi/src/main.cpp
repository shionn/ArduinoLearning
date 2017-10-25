#include <Arduino.h>
#include <SPI.h>

// chip select
#define CE 10
#define MOSI 11
#define CLOCK 13


void setup() {
	pinMode(CE,    OUTPUT);
	SPI.begin();
}

void loop() {
    // put your main code here, to run repeatedly:
}
