#include <ESP8266WiFi.h>

struct t_data {
    uint8_t test;
    unsigned short data;
    uint8_t end;
};


void setup() {
    Serial.begin( 9600 );
    Serial1.begin( 115200 ); // RX = ?, TX = D4
}

t_data data = { true, 42, 255 };

void loop() {
    data.data = random( 255 );
    Serial.print( "send " );
    Serial.print( sizeof( data ) );
    Serial.print( " " );
    Serial.println( data.data );
    Serial1.write( (uint8_t*)(&data), sizeof( data ) );
    delay( 1000 );
};;