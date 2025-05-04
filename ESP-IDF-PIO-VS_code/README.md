# ESP-IDF using PlatformIO plugin in VS Code

Path of least resistance. Once I remember how to create a new project using PlatformIO (PIO.)

## Status

## TODO

* 2025-05-03 create Blinky project.

## 2025-05-03 first steps

Open VS Code and PIO and create a new project with the following settings:

```text

[env:nodemcu-32s]
platform = espressif32
board = nodemcu-32s
framework = espidf
```

This produces an empty `main()` that builds and flashes w/out difficulty. Adding serial output was trivial. Adding GPIO was a bit less so, until I read the code I copied from and included the setup code. Doh!

The PIO IDE didn't create thje project where I expected (and desired) it be saved resulting in a directoryu structure that looked like 

```text
.../Fun_with_ESP32/ESP-IDF-PIO-VS_code/ESP-IDF-PIO-VS_code
```

It seems to have tolerated moving everytrhing from that directory up one. I've also built this on a laptop running Debian Trixie.

## 2025-05-04 add DS18B20 support

### background

This is a secondary goal of this exercise. I have an Arduino based project that does what I want but after running for a couple days or so, it stops working. <https://github.com/HankB/ESP32-Arduino-DS18B20_MQTT> I suspect that serial output is buffered and it just runs out of memory. If I disable all serial I/O, the project stops woprking. I recall running into this before.

I've got a similar project working on an ESP8266 <https://github.com/HankB/ESP8266_RTOS_DS18B20_publish> and which produces a *lot* of output in addition to publishing the DS18B20 temperature. There is also an Arduino variant <https://github.com/HankB/ESP8266_Arduino_MQTT_NTP_DS18B20>. I'm running each of these at present to see how long they keep running.

Back to DS18B20 support for the ESP-RTOS-SDK framework... It doesn't look like there is built in support. But... ESP-RTOS-SDK is for ESP8266. the correct search term is "ESP-IDF" or "ESP-SDK" and that leads me to <https://components.espressif.com/components/espressif/ds18b20>, but their examples do not have complete code. I'm a bit unsure about this so I'll start it in a branch `esp32-ds18b20`.

This attempt did not go well with the library failing to build. Check the `esp32-ds18b20` branch README for details. Moving on.