#include <Arduino.h>
#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino
#include <ESP8266HTTPClient.h> //https://github.com/esp8266/Arduino/libraries/ESP8266HTTPClient
#include <Arduino_JSON.h>

#define SSID "AsusHome"
#define SSID_PASS "aazzeerrttyy"


void waitWifiConnexion() {
    int tries = 0;
    while (!WiFi.isConnected()) {
        delay( 1000 );
        Serial.printf( "Connecting %d ...\n", tries++ );
    }
    Serial.print( "Connected " );
    Serial.println( WiFi.localIP() );
}

void setup() {
    // Serial.begin( 9600 );
    // int num = WiFi.scanNetworks();
    // for (int w = 0; w < num; w++) {
    //   Serial.println(WiFi.SSID( w));
    // }

    WiFi.disconnect();
    Serial.print( "Ethernet : " );
    Serial.println( WiFi.macAddress() );
    WiFi.enableAP( true );
    WiFi.setAutoConnect( true );
    WiFi.setAutoReconnect( true );
    WiFi.begin( SSID, SSID_PASS );
}

void loop() {
    waitWifiConnexion();

    HTTPClient http;
    if (http.begin( "http://192.168.50.58:8080/HomeIOT/alive" )) {
        int code = http.GET();
        Serial.printf( "http code : %d\n", code );
        if (code == HTTP_CODE_OK) {
            JSONVar obj = JSON.parse( http.getString() );
            for (int i = 0; i < obj.keys().length(); i++) {
                Serial.print( obj.keys()[i] );
                Serial.print( " : " );
                Serial.println( obj[obj.keys()[i]] );
            }
        } else {
            Serial.println( http.errorToString( code ) );
        }
    } else {
        Serial.println( "No begin" );
    }
    delay( 5000 );
}