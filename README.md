# SomfyDuinoHomeAssistant

[![CI](https://github.com/agileek/SomfyDuinoHomeAssistant/actions/workflows/CI.yaml/badge.svg)](https://github.com/agileek/SomfyDuinoHomeAssistant/actions/workflows/CI.yaml)

Control your somfy IO covers with Home Assistant through MQTT


**Based on the work done by Bjoern Foldenauer (https://create.arduino.cc/projecthub/beejayf/somfyduino-io-3d8283)**

## First step

I got a spare remote (Situo 5 io Pure II) that I opened and soldered, so that I won't have to by the crazy expensive (and closed source) somfy box to control my 3 veranda's covers.
Kudos to them, their board is really clean and self-documented, all I had to do was solder the cables on the labeled slots.

TODO: put image


## Getting Started, the terminal way

* Install arduino-cli
* `make init`

Now, copy DeviceConfig.hpp.template into DeviceConfig.hpp and configure the stuff: `cp ./DeviceConfig.hpp.template ./DeviceConfig.hpp`

Then, compile it: `make compile`

Finally, upload it: `make upload` (you can only use make upload, as it automatically compile)


## TODO

* Control each cover