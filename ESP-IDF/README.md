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

Change the example parameter to `2`, build and flash and now have a flashing blue LED. NB: `flash` does not automatically run `build` like the `make flash` command for the ESP8266.
