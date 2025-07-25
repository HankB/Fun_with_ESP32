# Fun_with_ESP32

Explore development environments for the ESP32 microcontroller.

## 2025-07-19 RISC-V update

I purchased a few more ESP32s (because for "reasons" I left the other ESPs at another location.) I went with the least expensive on Amazon described as:

> ESP32 ESP32-C3 Development Board ESP32 C3 Mini WiFi Bluetooth 160MHz Running Frequency 2.4GHz Wi-Fi & Bluetooth 5.0 ESP32 C3 Super mini for Arduino (5pcs) 

These seem to be officially named `ESP32-C3 Super Mini` and are RISC-V based. I will need to make some changes, but there seem to be at least several web pages that describe these boards well and of course the Espressif documents look good at first glance.

## Status

* 2025-07-18 (previous to) Three IDE/toolchains worked with the ESP32s I had that used the Tensilica cores. I took a stab at using the Arduino IDE with the ESP32-C3 and after installing the tool chain, it did not compile an example project so I set it aside.
*  2025-07-18 I added the ESP32C3 build tools (<https://docs.espressif.com/projects/esp-idf/en/stable/esp32c3/get-started/linux-macos-setup.html>) and successfully build and ran the `hello_world` and `blink` examples.

## 2025-04-15 Motivation

Explore various IDEs and frameworks that support S/W development for the ESP32 family of microcontrollers. This turned out to be a tougher challenge than expected for the ESP8266 <https://github.com/HankB/Fun_with_ESP8266> but perhaps that's because Espressif views it as a legacy product and doesn't provide much support for their tool kits. Expectations are higher for the ESP32. There are two families of frameworks for the ESP32, those provided directly by Espressif and FreeRTOS and those accessed via the Arduino frameworks. (I'm pretty sure the ARduino framework is a shim that accesses the Espressif frameworks under the skin.) IDEs include PlatformIO (PIO) through a VS Code plugin or a CLI, the Espressif ESP-IDF plugin for VS Code and the Arduino IDE, which now includes a command line (CLI) component.

My plan is to explore all of those (unless I find one that I like enough to terminate further exploration.) The exploration will be first the canonical embedded "Hello World": make an LED blink. The next will be to capture the readings from a Dallas DS18B20 temperature sensor which has proved surprisingly difficult on the ESP8266 (except for the Arduino framework.) A working Blinky insures that the toolchain works. DS18B20 readings are my ultimate goal at the moment. Related things like WiFi, NTP and MQTT are well supported and have been relatively straightforward.

## thoughts

* 2025-05-05 Two tool chains stand out at this point. 
    1. First is the Arduino (both IDE and CLI.) They're the simplest and most straightforward and probably the best choice for beginners.
    1. ESP-IDF as described in the Espressif documents. It. Just. Works.
    1. ESP-IDF plugin in VS Code did not configure due to inability to install Python modules directly. I could have tried to run it in a Python virtual environment but did not.
    1. PlatformIO was good for serial I/O and blinking an LED. I was stymied when it came to adding support for the DS18B20. Had I continued with this I might have been able to get it working, but got tired of rabbit holes.

## 2025-04-15 Plan

A tentative plan is:

1. Test the ESP-ICF CLI variant with the RISC-V based ESP32-C3.
1. Arduino IDE - this one I know and don't particularly care for, but it's a great starting point for someone without previous experience.
1. Arduino CLI - something new to me.
1. Espressif ESP-IDF via CLI. I don't recall if there is a non-OS variant (there probably is) but I'll go with the FreeRTOS variant.
1. ESP-IDF using the Espressif VS Code plugin.
1. ESP-IDF using the PIO VS Code plugin.
1. ESP-IDF using the PIO CLI.

## Errata

* My testing is done on an X86_64 laptop running Debian Testing (Trixie) and an X86_64 desktop running Debian Stable (Bookworm.)
