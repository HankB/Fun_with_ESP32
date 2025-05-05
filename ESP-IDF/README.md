# ESP-IDF 

Create a project using the ESP-IDF (with FreeRTOS) via CLI and without PlatformIO. But PlatformIO seems to be very convenient, so I may start with that instead. (as of 2025-05-03) I started with that and Serial and GPIO was very straight forward. Finding a DS18B20 driver was a maddening challenge and ultimately something I chose not to pursue.

## Status

* 2025-05-04 By the judicious selection of the right ESP-IDF example, Serial output and blinking LED are already working.

## 2025-05-04 getting started

May the 4th be with you!

* <https://docs.espressif.com/projects/esp-idf/en/stable/esp32/index.html>

> We highly recommend installing the ESP-IDF through your favorite IDE.

* <https://github.com/espressif/vscode-esp-idf-extension/blob/master/README.md> But this doesn't work because of Python ENV foolishness. Will perform the manual install.

```text
mkdir -p ~/esp
cd ~/esp
git clone -b v5.4.1 --recursive https://github.com/espressif/esp-idf.git
```

Next, set up the tools:

```text
cd ~/esp/esp-idf
./install.sh esp32
```

Tried to do this in a previously created venv (used for ESP8266) and it failed because it needed to create a virtual environment. Ran w/out the venv and it finished with 

```text
All done! You can now run:

  . ./export.sh

hbarta@olive:~/esp/esp-idf$ 
```

Woo! And I get:

```text
hbarta@olive:~/esp/esp-idf$ . ./export.sh
Checking "python3" ...
Python 3.11.2
"python3" has been detected
Activating ESP-IDF 5.4
warning:  IDF_PATH is changed from '/home/hbarta/esp/ESP8266_RTOS_SDK' to '/home/hbarta/esp/esp-idf'.
* Checking python version ... 3.11.2
* Checking python dependencies ... OK
* Deactivating the current ESP-IDF environment (if any) ... OK
* Establishing a new ESP-IDF environment ... OK
* Identifying shell ... bash
* Detecting outdated tools in system ... Found tools that are not used by active ESP-IDF version.
For removing old versions of xtensa-lx106-elf, esp32ulp-elf, xtensa-esp32s3-elf, esp32s2ulp-elf, openocd-esp32, xtensa-esp32s2-elf, xtensa-esp32-elf, riscv32-esp-elf use command 'python /home/hbarta/esp/esp-idf/tools/idf_tools.py uninstall'
To free up even more space, remove installation packages of those tools.
Use option python /home/hbarta/esp/esp-idf/tools/idf_tools.py uninstall --remove-archives.
* Shell completion ... Autocompletion code generated

Done! You can now compile ESP-IDF projects.
Go to the project directory and run:

  idf.py build
hbarta@olive:~/esp/esp-idf$ 
```

It looks like I need to run the followiung before building:

```text
. ~/esp/esp-idf/export.sh
```

Next, [Start a Project](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/linux-macos-setup.html#start-a-project)

(Diversion, I went to a different directory and built the `hello_world` project.)

```text
cp -r $IDF_PATH/examples/get-started/hello_world .
cd hello_world/
idf.py build
idf.py flash
idf.py monitor
```

And it all works. Now to browse the examples in `$IDF_PATH/examples` to decide which seems to be the most suitable starting point. That might be `$IDF_PATH/examples/get-started/blink`

```text
cp -r $IDF_PATH/examples/get-started/blink .
cd blink
idf.py set-target esp32
idf.py build
idf.py flash
```

And no flash. Examining the code looks like it is using GPIO 5. The built in (blue LED) is GPIO 2.

```text
idf.py menuconfig
```

Change the example parameter to `2`, build and flash and now have a flashing blue LED. NB: `flash` does not automatically run `build` like the `make flash` command for the ESP8266. Next up, it looks like the `$IDF_PATH/examples/peripherals/rmt/onewire` covers the `onewire` and DS18B20 driver.

## 2025-05-05 DS18B20 support

Perusing `newire` on the web site at <https://github.com/espressif/esp-idf/tree/master/examples/peripherals/rmt/onewire> I see `main/idf_component.yml` that contains:

```text
dependencies:
  ds18b20: "^0.1.0"
```

And the `blink` example has (which is not needed):

```text
dependencies:
  espressif/led_strip: "^2.4.1"
```

So just replace the `blink` dependency with the `onewire` one. After removing `#include "led_strip.h"` it builds. Before proceeding, remove all references to the LED strip in the code. And it works (tested with one sensor.) The output is:

```text
rst:0x1 (POWERON_RESET),boot:0x17 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0030,len:6276
load:0x40078000,len:15748
load:0x40080400,len:4
--- 0x40080400: _init at ??:?

ho 8 tail 4 room 4
load:0x40080404,len:3860
entry 0x4008063c
I (31) boot: ESP-IDF v5.4.1 2nd stage bootloader
I (31) boot: compile time May  5 2025 09:47:49
I (31) boot: Multicore bootloader
I (32) boot: chip revision: v1.0
I (35) boot.esp32: SPI Speed      : 40MHz
I (39) boot.esp32: SPI Mode       : DIO
I (42) boot.esp32: SPI Flash Size : 2MB
I (46) boot: Enabling RNG early entropy source...
I (50) boot: Partition Table:
I (53) boot: ## Label            Usage          Type ST Offset   Length
I (59) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (66) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (72) boot:  2 factory          factory app      00 00 00010000 00100000
I (79) boot: End of partition table
I (82) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=0bdd4h ( 48596) map
I (106) esp_image: segment 1: paddr=0001bdfc vaddr=3ff80000 size=0001ch (    28) load
I (106) esp_image: segment 2: paddr=0001be20 vaddr=3ffb0000 size=02684h (  9860) load
I (114) esp_image: segment 3: paddr=0001e4ac vaddr=40080000 size=01b6ch (  7020) load
I (120) esp_image: segment 4: paddr=00020020 vaddr=400d0020 size=18000h ( 98304) map
I (159) esp_image: segment 5: paddr=00038028 vaddr=40081b6c size=0c030h ( 49200) load
I (185) boot: Loaded app from partition at offset 0x10000
I (185) boot: Disabling RNG early entropy source...
I (195) cpu_start: Multicore app
I (203) cpu_start: Pro cpu start user code
I (204) cpu_start: cpu freq: 160000000 Hz
I (204) app_init: Application information:
I (204) app_init: Project name:     blink
I (207) app_init: App version:      205592f-dirty
I (212) app_init: Compile time:     May  5 2025 09:47:47
I (217) app_init: ELF file SHA256:  51989b59e...
I (221) app_init: ESP-IDF:          v5.4.1
I (225) efuse_init: Min chip rev:     v0.0
I (229) efuse_init: Max chip rev:     v3.99 
I (233) efuse_init: Chip rev:         v1.0
I (237) heap_init: Initializing. RAM available for dynamic allocation:
I (243) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (248) heap_init: At 3FFB2F78 len 0002D088 (180 KiB): DRAM
I (253) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (259) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (264) heap_init: At 4008DB9C len 00012464 (73 KiB): IRAM
I (271) spi_flash: detected chip: generic
I (273) spi_flash: flash io: dio
W (276) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (289) main_task: Started on CPU0
I (299) main_task: Calling app_main()
I (299) example: Example configured to blink GPIO LED!
I (299) gpio: GPIO[2]| InputEn: 0| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (309) example: 1-Wire bus installed on GPIO4
I (309) example: Device iterator created, start searching...
I (419) example: Found a DS18B20[0], address: F300000056D06828
I (419) example: Searching done, 1 DS18B20 device(s) found
I (429) example: Turning the LED OFF!
Does a simple printf() work? Yes!
I (1249) example: temperature read from DS18B20[0]: 23.62C
I (11249) example: Turning the LED ON!
Does a simple printf() work? Yes!
I (12059) example: temperature read from DS18B20[0]: 23.62C
I (22059) example: Turning the LED OFF!
Does a simple printf() work? Yes!
I (22869) example: temperature read from DS18B20[0]: 23.62C
I (32869) example: Turning the LED ON!
Does a simple printf() work? Yes!
I (33679) example: temperature read from DS18B20[0]: 23.62C
```

Done! And using the ESP-IDF w/out PlatformIO or VS Code extensions is not that difficult. No rabbit holes.
