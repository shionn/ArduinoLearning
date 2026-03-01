#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoHA.h>
#include "ArduinoHADefines.h"

#define SSID_NAME "AsusHome"
#define SSID_PASS "aazzeerrttyy"
#define HOST_NAME "HaTestLight"

byte mac[] = { 0x3C, 0x61, 0x05, 0xD0, 0xB9, 0x87 };

WiFiClient client;

HADevice device(mac, sizeof(mac));
HAMqtt mqtt(client, device);
HALight light("HaTestLightDevice", HALight::BrightnessFeature | HALight::ColorTemperatureFeature | HALight::RGBFeature);

void initWifi() {
	WiFi.disconnect(true);
	// il faut faire le setHostName avant le mode sinon ce n'est pas pris en compte. 
	WiFi.setHostname(HOST_NAME);
	// mode client
	WiFi.mode(WIFI_STA);
	WiFi.setAutoConnect(true);
	WiFi.setAutoReconnect(true);
	WiFi.begin(SSID_NAME, SSID_PASS);

	while (!WiFi.isConnected()) {
		Serial.print(".");
		delay(100);
	}
	Serial.println();
	Serial.print("Connected. Ip: ");
	Serial.println(WiFi.localIP().toString());

	Serial.print("Connected. Mac: ");
	Serial.println(WiFi.macAddress());
}

void onStateChanged(HAMqtt::ConnectionState state) {
	Serial.print("onStateChanged: ");
	Serial.println(state);

}

void setup() {
	Serial.begin(9600);

	initWifi();

	mqtt.onStateChanged(onStateChanged);
	mqtt.begin("192.168.10.129");
}

void loop() {
	mqtt.loop();

}
