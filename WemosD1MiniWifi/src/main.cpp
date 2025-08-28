#include <Arduino.h>
// #include <WiFi.h>
#include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
// #include <WiFiClientSecure.h>

#include <WiFiUdp.h>
#include <NTPClient.h>
#include <Timezone.h>

#define SSID_NAME "AsusHome"
#define SSID_PASS "aazzeerrttyy"
#define HOST_NAME "Esp8266Dev"


// #define HOST "https://shionn.github.io/" 

// WiFiClientSecure client;
// HTTPClient http;

#define NTP_SERVER "pool.ntp.org"
#define REFRESH_INTERVAL_IN_MS 600000

WiFiUDP udp;
NTPClient timeClient(udp, NTP_SERVER, 0, REFRESH_INTERVAL_IN_MS);
TimeChangeRule cest = { "CEST", Last, Sun, Mar, 2, 120 };
TimeChangeRule cet = { "CET", Last, Sun, Oct, 3, 60 };
Timezone timezone(cest, cet);

void setup() {
	Serial.begin(9600);
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

	timeClient.begin();
}

void loop() {
	timeClient.update();
	time_t utcTime = timeClient.getEpochTime();
	time_t localTime = timezone.toLocal(utcTime);

	Serial.print("Heure : ");
	Serial.println(ctime(&localTime));

	delay(1000);
}
