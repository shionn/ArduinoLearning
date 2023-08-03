#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define STRIP_COUNT 120
#define STRIP_PIN PIN5

Adafruit_NeoPixel strip(STRIP_COUNT, STRIP_PIN, NEO_GRB + NEO_KHZ800);



void setup() {
  strip.begin();
  strip.show();
}

int8_t step = 0;

void loop() {
  for (int8_t led = 0; led < STRIP_COUNT; led++) {
    uint16_t hue = map(led + step, 0, 128, 0, 65535);
    strip.setPixelColor(led, strip.ColorHSV(hue, 255, 255));
  }
  strip.show();
  step++;
}

