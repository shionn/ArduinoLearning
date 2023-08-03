#include <Arduino.h>
#include <TM1637Display.h>
#include <DHTesp.h>

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

#define LETTER_C SEG_A | SEG_D | SEG_E | SEG_F


DHTesp dht;
TM1637Display display(  D2, // CLOCK Blanc
                        D3); // DATA Jaune

void setup() {
  Serial.begin(9600);
  Serial.println("-- started --");
  dht.setup(D1, DHTesp::DHT22);
  display.setBrightness(0x0f);
}

void loop() {
  delay(2000);
  float temperature = dht.getTemperature();
  Serial.println(temperature);
  uint8_t data[] = { LETTER_C };
  display.showNumberDecEx(temperature*10, 0b11100000, false, 3, 0);
  display.setSegments(data, 1, 3);
}
