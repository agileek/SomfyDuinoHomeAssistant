#include "DeviceConfig.hpp"


#include <ESP8266WiFi.h>

#include <ArduinoHA.h>

// MQTT setup
HADevice device;

WiFiClient client;

HAMqtt mqtt(client, device);
HACover cover(DEVICE_NAME);


int downPin = D5;
int selectPin = D6;
int myPin = D7;
int upPin = D8;

unsigned long holdTime = 500;

void setup() {
  Serial.begin(9600);

  Serial.println("Init");
  pinMode(upPin, OUTPUT);
  Serial.println("Up");
  pinMode(downPin, OUTPUT);
  Serial.println("Down");
  pinMode(myPin, OUTPUT);
  Serial.println("My");
  pinMode(selectPin, OUTPUT);
  Serial.println("Select");
  digitalWrite(upPin, HIGH);
  Serial.println("Up");
  digitalWrite(downPin, HIGH);
  Serial.println("Down");
  digitalWrite(myPin, HIGH);
  Serial.println("My");
  digitalWrite(selectPin, HIGH);
  Serial.println("Select");


	Serial.println("Setup WiFi");
	WiFi.begin(WI_FI_SSID, WI_FI_PASSWORD);
	Serial.println("");

	while (WiFi.status() != WL_CONNECTED) {
		delay(100);
		Serial.print(".");
	}

	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(WI_FI_SSID);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	Serial.print("MAC address: ");
	Serial.println(WiFi.macAddress());
	Serial.print("Hostname: ");
	Serial.println(String(WiFi.hostname()));

  byte mac[WL_MAC_ADDR_LENGTH];
	WiFi.macAddress(mac);
  device.setUniqueId(mac, sizeof(mac));
	device.setName(DEVICE_NAME);

  cover.onCommand(onCoverCommand);
  cover.setName(DEVICE_NAME);
  cover.setRetain(true);
  if (MQTT_AUTHENTICATION) {
		mqtt.begin(MQTT_ADDR, MQTT_USERNAME, MQTT_PASSWORD);
	} else {
		mqtt.begin(MQTT_ADDR);
	}
}

void loop() {
    mqtt.loop();
}

void onCoverCommand(HACover::CoverCommand cmd) {
    if (cmd == HACover::CommandOpen) {
        Serial.println("Command: Open");
        cover.setState(HACover::StateOpening);
        digitalWrite(upPin, LOW);
        delay(holdTime);
        digitalWrite(upPin, HIGH);
        cover.setState(HACover::StateOpen);
        cover.setPosition(100);
    } else if (cmd == HACover::CommandClose) {
        Serial.println("Command: Close");
        cover.setState(HACover::StateClosing);
        digitalWrite(downPin, LOW);
        delay(holdTime);
        digitalWrite(downPin, HIGH);
        cover.setState(HACover::StateClosed);
        cover.setPosition(0);
    } else if (cmd == HACover::CommandStop) {
        Serial.println("Command: Stop");
        cover.setState(HACover::StateStopped);
        digitalWrite(myPin, LOW);
        delay(holdTime);
        digitalWrite(myPin, HIGH);
    }
}