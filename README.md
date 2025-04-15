# Fun_with_ESP32

Explore development environments for the ESP32 microcontroller.

## 2025-04-15 Motivation

Explore various IDEs and frameworks that support S/W development for the ESP32 family of microcontrollers. This turned out to be a tougher challenge than expected for the ESP8266 <https://github.com/HankB/Fun_with_ESP8266> but perhaps that's because Espressif views it as a legacy product and doesn't provide much support for their tool kits. Expectations are higher for the ESP32. There are two families of frameworks for the ESP32, those provided directly by Espressif and FreeRTOS and those accessed via the Arduino frameworks. (I'm pretty sure the ARduino framework is a shim that accesses the Espressif frameworks under the skin.) IDEs include PlatformIO (PIO) through a VS Code plugin or a CLI, the Espressif ESP-IDF plugin for VS Code and the Arduino IDE, which now includes a command line (CLI) component.

My plan is to explore all of those (unless I find one that I like enough to terminate further exploration.) The exploration will be first the canonical embedded "Hello World": make an LED blink. The next will be to capture the readings from a Dallas DS18B20 temperature sensor which has proved surprisingly difficult on the ESP8266 (except for the Arduino framework.) A working Blinky insures that the toolchain works. DS18B20 readings are my ultimate goal at the moment. Related things like WiFi, NTP and MQTT are well supported and have been relatively straightforward.

## 2025-04-15 Plan

A tentative plan is:

1. Arduino IDE - this one I know and don't particularly care for, but it's a great starting point for someone without previous experience.
1. Arduino CLI - something new to me.
1. Espressif ESP-IDF via CLI. I don't recall if there is a non-OS variant (there probably is) but I'll go with the FreeRTOS variant.
1. ESP-IDF using the Espressif VS Code plugin.
1. ESP-IDF using the PIO VS Code plugin.
1. ESP-IDF using the PIO CLI.

## Errata

* My testing is done on an X86_64 laptop running Debian Testing (Trixie) and an X86_64 desktop running Debian Stable (Bookworm.)
