# Arduino IDE

## 2025-04-15 Setup

Download the AppImage `from <https://www.arduino.cc/en/software/> and place it somewhere convenient, give it a reasonably short name, make it esecutable and run it. Debian includes an Arduino IDE package in the repos but it's pretty old.

```text
mv ~/Downloads/arduino-ide_2.3.6_Linux_64bit.AppImage ~/bin/
ln ~/bin/arduino-ide_2.3.6_Linux_64bit.AppImage ~/bin/arduino
chmod +x ~/bin/arduino-ide_2.3.6_Linux_64bit.AppImage
arduino
```

Starting it brings up the editor and prompts to update some built in libraries. I click "Manually Install" and none of them looks relevant to this effort so I swtch to the file folder tab. The IDE comes up with a "Blinky" example. Where's the fun in that? Connect the ESP32 (NodeMCU or clone, IIRC), select the board and device (`/dev/ttyUSB0`)

* Tools -> Board -> ESP32 Arduino -> NodeMCU-32S (The dev oard says `ESP32S` on the underside.)
* Connect the ESP32 via USB cable.
* Tools -> Port -> /dev/ttyUSB0
* Click right arrow (upper right) to compile and flash the sketch.
* `<ctrl>M` to bring up the serial monitor. View gibberish.
* Open the baud rate drop down (upper left, monitor window) and select 115200.

Great Success! But the sketch advises that one can use the internal LED or the serial console but not both at the same time so all I see is

```text
led would be off
led would be on
led would be off
led would be on
led would be off
led would be on
...
```

Pressing the reset button gets the boot message too.

```text
ets Jun  8 2016 00:22:57

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:1
load:0x3fff0018,len:4
load:0x3fff001c,len:928
ho 0 tail 12 room 4
load:0x40078000,len:8424
ho 0 tail 12 room 4
load:0x40080400,len:5868
entry 0x4008069c
led would be on
...
```

Change the `use_serial` definition to `0` and now the blue LED flashes. Time to Save! (Way past time to save...) Click "File -> Save As" and navigate to this directory, enter the sketch name "blinky" and save. The result is:

```text
hbarta@rocinante:~/Programming/ESP32/Fun_with_ESP32/Arduino-IDE$ tree
.
├── blinky
│   └── blinky.ino
└── README.md

2 directories, 2 files
hbarta@rocinante:~/Programming/ESP32/Fun_with_ESP32/Arduino-IDE$ 
```

"File -> Preferences" and Autosave is there and default on. One giant step for mankind. Next "Tools -> Library manager and ehter "DS18B20" in the search field. There are a bunch of hits, the first of which "more info" links to <https://github.com/matmunk/DS18B20>, but first commit and push.


