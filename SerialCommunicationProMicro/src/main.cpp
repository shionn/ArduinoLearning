#include <Arduino.h>



void setup() {
    Serial.begin( 9600 ); // USB
    Serial1.begin( 115200 ); // TX0 , RX1
    Serial1.setTimeout( 10000 );
    Serial1.flush();
}

struct t_data {
    uint8_t test;
    unsigned short data;
    uint8_t end;
};

t_data data = { false, 0 };

void loop() {
    if (Serial1.available() >= sizeof( data )) {
        Serial.print( Serial1.available() );
        Serial.print( ' ' );
        Serial.print( sizeof( data ) );
        Serial.print( ' ' );
        Serial.print( Serial1.readBytes( (uint8_t*)(&data), sizeof( data ) ) );
        Serial.print( ' ' );
        Serial.print( data.test );
        Serial.print( ' ' );
        Serial.println( data.data );
        while (Serial1.available()) Serial1.read();
    }

}