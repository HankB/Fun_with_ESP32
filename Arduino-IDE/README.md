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

"File -> Preferences" and Autosave is there and default on. One giant step for mankind. Next "Tools -> Library manager and enter "DS18B20" in the search field. There are a bunch of hits, the first of which "more info" links to <https://github.com/matmunk/DS18B20>, but first commit and push.

## 2025-04-15 DS18B20

Install `DS18B20 by Matthias Munk Hansen` and go to the example <https://github.com/matmunk/DS18B20/blob/master/examples/Multiple/Multiple.ino> and copy/paste some code to my `blinky` sketch. (I have one sensor connected at present but plan to use more in the future.) Add code from `setup()` and try to build.

```text
In file included from /home/hbarta/Programming/ESP32/Fun_with_ESP32/Arduino-IDE/blinky/blinky.ino:16:
/home/hbarta/Arduino/libraries/DS18B20/src/DS18B20.h:5:10: fatal error: OneWire.h: No such file or directory
    5 | #include <OneWire.h>
      |          ^~~~~~~~~~~
compilation terminated.
exit status 1

Compilation error: exit status 1
```

Check the README <https://github.com/matmunk/DS18B20> and note the instructions to install the `onewire` library. Finding that in the Library Manager as `OneWire by Jim Studt, Tom Pollard, Robin James (and more)`. Install v2.3.8. The sketch now builds and after flashing... Not flashing.

```text
Sketch uses 299234 bytes (22%) of program storage space. Maximum is 1310720 bytes.
Global variables use 20540 bytes (6%) of dynamic memory, leaving 307140 bytes for local variables. Maximum is 327680 bytes.
esptool.py v4.8.1
Serial port /dev/ttyUSB0
Connecting......................................

A fatal error occurred: Failed to connect to ESP32: Wrong boot mode detected (0x1b)! The chip needs to be in download mode.
For troubleshooting steps visit: https://docs.espressif.com/projects/esptool/en/latest/troubleshooting.html
Failed uploading: uploading error: exit status 2
```

This is a new one for me. Particularly odd since the sketch worked previously. Commentiong out the new code does not help. Restarting the IDE - same issue. Espressif link - not much help, Looking for a different library by entering search terms "DS18B20 ESP32" and find <https://github.com/junkfix/esp32-ds18b20> which I install.