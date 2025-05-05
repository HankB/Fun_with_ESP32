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

### find a DS18B20 driver

Back to DS18B20 support for the ESP-RTOS-SDK framework... It doesn't look like there is built in support. But... ESP-RTOS-SDK is for ESP8266. the correct search term is "ESP-IDF" or "ESP-SDK" and that leads me to <https://components.espressif.com/components/espressif/ds18b20>, but their examples do not have complete code. 

Found <https://github.com/DavidAntliff/esp32-ds18b20>. I'm a bit unsure about this so I'll start it in a branch `esp32-ds18b20`.This attempt did not go well with the library failing to build. Check the `esp32-ds18b20` branch README for details. Moving on.

Next found: <https://github.com/espressif/esp-idf/tree/master/examples/peripherals/rmt/onewire> and perhaps this is related to <https://components.espressif.com/components/espressif/ds18b20>. Having a go with it using branch `espressif-ds18b20`.

Installing <https://components.espressif.com/components/espressif/ds18b20> also requires <https://components.espressif.com/components/espressif/onewire_bus>. Adding the dependencies to `platformio.ini` following the pattern at <https://github.com/espressif/esp-idf/blob/master/examples/peripherals/rmt/onewire/main/idf_component.yml>

```text
[env:nodemcu-32s]
platform = espressif32
board = nodemcu-32s
framework = espidf
monitor_speed = 115200
dependencies:
  ds18b20: "^0.1.0"
  onewire_bus: "^1.0.2"
```

Build works. Now some code from <https://github.com/espressif/esp-idf/blob/master/examples/peripherals/rmt/onewire/main/onewire_example_main.c>

After adding some code to `main.c` - mostly includes - the build fails.

```text
Compiling .pio/build/nodemcu-32s/src/main.c.o
src/main.c:15:10: fatal error: onewire_bus.h: No such file or directory

*********************************************************************
* Looking for onewire_bus.h dependency? Check our library registry!
*
* CLI  > platformio lib search "header:onewire_bus.h"
* Web  > https://registry.platformio.org/search?q=header:onewire_bus.h
*
*********************************************************************

   15 | #include "onewire_bus.h"
      |          ^~~~~~~~~~~~~~~
compilation terminated.
Compiling .pio/build/nodemcu-32s/lib7dc/esp32-owb/owb.o
*** [.pio/build/nodemcu-32s/src/main.c.o] Error 1
In file included from .pio/libdeps/nodemcu-32s/esp32-owb/include/owb_rmt.h:41,
                 from .pio/libdeps/nodemcu-32s/esp32-owb/include/owb.h:329,
                 from .pio/libdeps/nodemcu-32s/esp32-owb/owb.c:42:
/home/hbarta/.platformio/packages/framework-espidf/components/driver/deprecated/driver/rmt.h:18:2: warning: #warning "The legacy RMT driver is deprecated, please use driver/rmt_tx.h and/or driver/rmt_rx.h" [-Wcpp]
   18 | #warning "The legacy RMT driver is deprecated, please use driver/rmt_tx.h and/or driver/rmt_rx.h"
      |  ^~~~~~~
=========================================== [FAILED] Took 1.92 seconds ===========================================
```

Digging into this, it seems like another rabbit hole. I got to <https://docs.platformio.org/en/latest/frameworks/espidf.html> where I find under "There are two possible ways of adding extra components to PlatformIO project:"

> By adding a new component to an optional folder called `components` in the root of your project. This folder will be automatically scanned for valid components.

I'll give that a try. First clone <https://github.com/espressif/idf-extra-components?tab=readme-ov-file> (Into `~/Downloads`)

```text
cd ~/Downloads
git clone https://github.com/espressif/idf-extra-components.git
find idf-extra-components -name onewire_bus
cp -R idf-extra-components/onewire_bus ~/Programming/ESP32/Fun_with_ESP32/ESP-IDF-PIO-VS_code/components
```

And remove the dependencies from `platformio.ini` and build. Result is a crap-ton of warnings and errors.

```text
Compiling .pio/build/nodemcu-32s/lib7dc/esp32-owb/owb_rmt.o
In file included from .pio/libdeps/nodemcu-32s/esp32-owb/include/owb_rmt.h:41,
                 from .pio/libdeps/nodemcu-32s/esp32-owb/include/owb.h:329,
                 from .pio/libdeps/nodemcu-32s/esp32-owb/owb_gpio.c:42:
/home/hbarta/.platformio/packages/framework-espidf/components/driver/deprecated/driver/rmt.h:18:2: warning: #warning "The legacy RMT driver is deprecated, please use driver/rmt_tx.h and/or driver/rmt_rx.h" [-Wcpp]
   18 | #warning "The legacy RMT driver is deprecated, please use driver/rmt_tx.h and/or driver/rmt_rx.h"
      |  ^~~~~~~
In file included from .pio/libdeps/nodemcu-32s/esp32-owb/include/owb_rmt.h:41,
                 from .pio/libdeps/nodemcu-32s/esp32-owb/include/owb.h:329,
                 from .pio/libdeps/nodemcu-32s/esp32-owb/owb.c:42:
/home/hbarta/.platformio/packages/framework-espidf/components/driver/deprecated/driver/rmt.h:18:2: warning: #warning "The legacy RMT driver is deprecated, please use driver/rmt_tx.h and/or driver/rmt_rx.h" [-Wcpp]
   18 | #warning "The legacy RMT driver is deprecated, please use driver/rmt_tx.h and/or driver/rmt_rx.h"
      |  ^~~~~~~
.pio/libdeps/nodemcu-32s/esp32-owb/owb_gpio.c: In function '_us_delay':
.pio/libdeps/nodemcu-32s/esp32-owb/owb_gpio.c:85:5: error: implicit declaration of function 'ets_delay_us' [-Wimplicit-function-declaration]
   85 |     ets_delay_us(time_us);
      |     ^~~~~~~~~~~~
In file included from .pio/libdeps/nodemcu-32s/esp32-owb/include/owb_rmt.h:41,
                 from .pio/libdeps/nodemcu-32s/esp32-owb/include/owb.h:329,
                 from .pio/libdeps/nodemcu-32s/esp32-owb/owb_rmt.c:59:
/home/hbarta/.platformio/packages/framework-espidf/components/driver/deprecated/driver/rmt.h:18:2: warning: #warning "The legacy RMT driver is deprecated, please use driver/rmt_tx.h and/or driver/rmt_rx.h" [-Wcpp]
   18 | #warning "The legacy RMT driver is deprecated, please use driver/rmt_tx.h and/or driver/rmt_rx.h"
      |  ^~~~~~~
.pio/libdeps/nodemcu-32s/esp32-owb/owb_gpio.c: In function 'owb_gpio_initialize':
.pio/libdeps/nodemcu-32s/esp32-owb/owb_gpio.c:273:5: error: implicit declaration of function 'gpio_pad_select_gpio'; did you mean 'esp_rom_gpio_pad_select_gpio'? [-Wimplicit-function-declaration]
  273 |     gpio_pad_select_gpio(driver_info->gpio);
      |     ^~~~~~~~~~~~~~~~~~~~
      |     esp_rom_gpio_pad_select_gpio
.pio/libdeps/nodemcu-32s/esp32-owb/owb_rmt.c: In function '_init':
.pio/libdeps/nodemcu-32s/esp32-owb/owb_rmt.c:428:9: error: 'GPIO' undeclared (first use in this function)
  428 |         GPIO.enable_w1ts = (0x1 << gpio_num);
      |         ^~~~
.pio/libdeps/nodemcu-32s/esp32-owb/owb_rmt.c:428:9: note: each undeclared identifier is reported only once for each function it appears in
.pio/libdeps/nodemcu-32s/esp32-owb/owb_rmt.c:438:5: error: implicit declaration of function 'rmt_set_pin'; did you mean 'rmt_set_gpio'? [-Wimplicit-function-declaration]
  438 |     rmt_set_pin(info->rx_channel, RMT_MODE_RX, gpio_num);
      |     ^~~~~~~~~~~
      |     rmt_set_gpio
.pio/libdeps/nodemcu-32s/esp32-owb/owb_rmt.c:442:5: error: implicit declaration of function 'PIN_INPUT_ENABLE' [-Wimplicit-function-declaration]
  442 |     PIN_INPUT_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
      |     ^~~~~~~~~~~~~~~~
.pio/libdeps/nodemcu-32s/esp32-owb/owb_rmt.c:442:22: error: 'GPIO_PIN_MUX_REG' undeclared (first use in this function)
  442 |     PIN_INPUT_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
      |                      ^~~~~~~~~~~~~~~~
Compiling .pio/build/nodemcu-32s/libdbc/esp32-ds18b20/ds18b20.o
*** [.pio/build/nodemcu-32s/lib7dc/esp32-owb/owb_gpio.o] Error 1
*** [.pio/build/nodemcu-32s/lib7dc/esp32-owb/owb_rmt.o] Error 1
In file included from .pio/libdeps/nodemcu-32s/esp32-owb/include/owb_rmt.h:41,
                 from .pio/libdeps/nodemcu-32s/esp32-owb/include/owb.h:329,
                 from .pio/libdeps/nodemcu-32s/esp32-ds18b20/include/ds18b20.h:37,
                 from .pio/libdeps/nodemcu-32s/esp32-ds18b20/ds18b20.c:47:
/home/hbarta/.platformio/packages/framework-espidf/components/driver/deprecated/driver/rmt.h:18:2: warning: #warning "The legacy RMT driver is deprecated, please use driver/rmt_tx.h and/or driver/rmt_rx.h" [-Wcpp]
   18 | #warning "The legacy RMT driver is deprecated, please use driver/rmt_tx.h and/or driver/rmt_rx.h"
      |  ^~~~~~~
.pio/libdeps/nodemcu-32s/esp32-ds18b20/ds18b20.c: In function '_wait_for_duration':
.pio/libdeps/nodemcu-32s/esp32-ds18b20/ds18b20.c:149:26: error: implicit declaration of function 'esp_timer_get_time' [-Wimplicit-function-declaration]
  149 |     int64_t start_time = esp_timer_get_time();
      |                          ^~~~~~~~~~~~~~~~~~
*** [.pio/build/nodemcu-32s/libdbc/esp32-ds18b20/ds18b20.o] Error 1
========================================================== [FAILED] Took 12.72 seconds ==========================================================
```

Setting this aside for now.
