#include <Arduino.h>



void setup() {
    pinMode( LED_BUILTIN, OUTPUT );
    pinMode( PIN4, INPUT );
}

void loop() {
    if (digitalRead( PIN4 ) == HIGH) {
        digitalWrite( LED_BUILTIN, HIGH );
    } else {
        digitalWrite( LED_BUILTIN, LOW );
    }
}