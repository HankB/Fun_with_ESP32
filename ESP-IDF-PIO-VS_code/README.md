# ESP-IDF using PlatformIO plugin in VS Code

Path of least resistance. Once I remember how to create a new project using PlatformIO (PIO.)

## Status

* 2025-05-03 project prints "hello world" and flashes an LED.

## TODO

* ~~2025-05-03 create Blinky project.~~
* 2025-05-04 Add DS18B20 support.

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

### Adding DS18B20

* Search for `espressif/ds18b20` in the library manager.
* Click "esp32-DS18B20 by David Antiff" and peruse the Github page. Seems to have everything I want. (Full example...)
* Click "Add to Project" and see the additional line in `platformio.ini`

```text
[env:nodemcu-32s]
platform = espressif32
board = nodemcu-32s
framework = espidf
monitor_speed = 115200
lib_deps = abraha2d/esp32-ds18b20@^0.1 <<<<<<<<< new line
```

* Present code in `main.c` is only 56 lines so I will just add the DS18B20 code there, coping slavishly from the example. When trying to build, I find I need to add `abraha2d/esp32-ds18b20@^0.1` as well, yielding:

```text
[env:nodemcu-32s]
platform = espressif32
board = nodemcu-32s
framework = espidf
monitor_speed = 115200
lib_deps = 
	abraha2d/esp32-ds18b20@^0.1
	davidantliff/esp32-owb@^0.1
```

And now the library fails to build:

```text
Compiling .pio/build/nodemcu-32s/lib7dc/esp32-owb/owb_rmt.o
In file included from .pio/libdeps/nodemcu-32s/esp32-owb/include/owb_rmt.h:41,
                 from .pio/libdeps/nodemcu-32s/esp32-owb/include/owb.h:329,
                 from .pio/libdeps/nodemcu-32s/esp32-owb/owb.c:42:
/home/hbarta/.platformio/packages/framework-espidf/components/driver/deprecated/driver/rmt.h:18:2: warning: #warning "The legacy RMT driver is deprecated, please use driver/rmt_tx.h and/or driver/rmt_rx.h" [-Wcpp]
   18 | #warning "The legacy RMT driver is deprecated, please use driver/rmt_tx.h and/or driver/rmt_rx.h"
      |  ^~~~~~~
.pio/libdeps/nodemcu-32s/esp32-owb/owb.c: In function 'owb_use_strong_pullup_gpio':
.pio/libdeps/nodemcu-32s/esp32-owb/owb.c:345:13: error: implicit declaration of function 'gpio_pad_select_gpio'; did you mean 'esp_rom_gpio_pad_select_gpio'? [-Wimplicit-function-declaration]
  345 |             gpio_pad_select_gpio(gpio);
      |             ^~~~~~~~~~~~~~~~~~~~
      |             esp_rom_gpio_pad_select_gpio
In file included from .pio/libdeps/nodemcu-32s/esp32-owb/include/owb_rmt.h:41,
                 from .pio/libdeps/nodemcu-32s/esp32-owb/include/owb.h:329,
                 from .pio/libdeps/nodemcu-32s/esp32-owb/owb_gpio.c:42:
/home/hbarta/.platformio/packages/framework-espidf/components/driver/deprecated/driver/rmt.h:18:2: warning: #warning "The legacy RMT driver is deprecated, please use driver/rmt_tx.h and/or driver/rmt_rx.h" [-Wcpp]
   18 | #warning "The legacy RMT driver is deprecated, please use driver/rmt_tx.h and/or driver/rmt_rx.h"
      |  ^~~~~~~
.pio/libdeps/nodemcu-32s/esp32-owb/owb_gpio.c: In function '_us_delay':
.pio/libdeps/nodemcu-32s/esp32-owb/owb_gpio.c:85:5: error: implicit declaration of function 'ets_delay_us' [-Wimplicit-function-declaration]
Compiling .pio/build/nodemcu-32s/libdbc/esp32-ds18b20/ds18b20.o
   85 |     ets_delay_us(time_us);
      |     ^~~~~~~~~~~~
In file included from .pio/libdeps/nodemcu-32s/esp32-owb/include/owb_rmt.h:41,
                 from .pio/libdeps/nodemcu-32s/esp32-owb/include/owb.h:329,
                 from .pio/libdeps/nodemcu-32s/esp32-owb/owb_rmt.c:59:
/home/hbarta/.platformio/packages/framework-espidf/components/driver/deprecated/driver/rmt.h:18:2: warning: #warning "The legacy RMT driver is deprecated, please use driver/rmt_tx.h and/or driver/rmt_rx.h" [-Wcpp]
   18 | #warning "The legacy RMT driver is deprecated, please use driver/rmt_tx.h and/or driver/rmt_rx.h"
      |  ^~~~~~~
*** [.pio/build/nodemcu-32s/lib7dc/esp32-owb/owb.o] Error 1
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
*** [.pio/build/nodemcu-32s/lib7dc/esp32-owb/owb_gpio.o] Error 1
.pio/libdeps/nodemcu-32s/esp32-owb/owb_rmt.c:442:5: error: implicit declaration of function 'PIN_INPUT_ENABLE' [-Wimplicit-function-declaration]
  442 |     PIN_INPUT_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
      |     ^~~~~~~~~~~~~~~~
.pio/libdeps/nodemcu-32s/esp32-owb/owb_rmt.c:442:22: error: 'GPIO_PIN_MUX_REG' undeclared (first use in this function)
  442 |     PIN_INPUT_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
      |                      ^~~~~~~~~~~~~~~~
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
```

I wonder how far I want to go down this rabbit hole. No, too many errors. Setting this aside for now.
