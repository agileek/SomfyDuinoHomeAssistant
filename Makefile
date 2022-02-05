debug:
	arduino-cli board list

init:
	arduino-cli core install esp8266:esp8266
	arduino-cli lib install "home-assistant-integration"@1.3.0

compile:
	arduino-cli compile --fqbn esp8266:esp8266:d1_mini ./SomfyDuinoHomeAssistant.ino


upload: compile
	arduino-cli upload --fqbn esp8266:esp8266:d1_mini ./SomfyDuinoHomeAssistant.ino --port /dev/ttyUSB0


monitor:
	arduino-cli monitor --port /dev/ttyUSB0

