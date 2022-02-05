#include "DeviceConfig.hpp"

// Sanity check
#if ENABLE_MQTT && !ENABLE_WI_FI
	#error Wi-Fi must be enabled for MQTT to work properly
#endif

#if ENABLE_WI_FI
  #include <ESP8266WiFi.h>
#endif

#if ENABLE_MQTT
	#include <ArduinoHA.h>


HADevice device;

WiFiClient client;

HAMqtt mqtt(client, device);
HACover cover(DEVICE_NAME);

#endif


int downPin = D5;
int selectPin = D6;
int myPin = D7;
int upPin = D8;

boolean upPress = false;
boolean downPress = false;
boolean myPress = false;
boolean selectPress = false;
unsigned long holdTime = 500;
int repeatSend = 0;

char incomingChar;

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


#if ENABLE_WI_FI
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
#endif

#if ENABLE_MQTT
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
#endif
}

void loop() {
#if ENABLE_MQTT
    mqtt.loop();
#endif
}

void onCoverCommand(HACover::CoverCommand cmd) {
    if (cmd == HACover::CommandOpen) {
        Serial.println("Command: Open");
        cover.setState(HACover::StateOpening);
        digitalWrite(upPin, LOW);
        delay(holdTime);
        digitalWrite(upPin, HIGH);
        cover.setState(HACover::StateOpen);
    } else if (cmd == HACover::CommandClose) {
        Serial.println("Command: Close");
        cover.setState(HACover::StateClosing);
        digitalWrite(downPin, LOW);
        delay(holdTime);
        digitalWrite(downPin, HIGH);
        cover.setState(HACover::StateClosed);
    } else if (cmd == HACover::CommandStop) {
        Serial.println("Command: Stop");
        cover.setState(HACover::StateStopped);
        digitalWrite(myPin, LOW);
        delay(holdTime);
        digitalWrite(myPin, HIGH);
    }

    // Available states:
    // HACover::StateClosed
    // HACover::StateClosing
    // HACover::StateOpen
    // HACover::StateOpening
    // HACover::StateStopped

    // You can also report position using setPosition() method
}