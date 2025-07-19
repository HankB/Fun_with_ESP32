| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C5 | ESP32-C6 | ESP32-C61 | ESP32-H2 | ESP32-P4 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | --------- | -------- | -------- | -------- | -------- |

# Blink Example

(See the README.md file in the upper level 'examples' directory for more information about examples.)

This example demonstrates how to blink a LED by using the GPIO driver or using the [led_strip](https://components.espressif.com/component/espressif/led_strip) library if the LED is addressable e.g. [WS2812](https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf). The `led_strip` library is installed via [component manager](main/idf_component.yml).

## How to Use Example

Before project configuration and build, be sure to set the correct chip target using `idf.py set-target <chip_name>`.

### Hardware Required

* A development board with normal LED or addressable LED on-board (e.g., ESP32-S3-DevKitC, ESP32-C6-DevKitC etc.)
* A USB cable for Power supply and programming

See [Development Boards](https://www.espressif.com/en/products/devkits) for more information about it.

### Configure the Project

Open the project configuration menu (`idf.py menuconfig`).

In the `Example Configuration` menu:

* Select the LED type in the `Blink LED type` option.
  * Use `GPIO` for regular LED
  * Use `LED strip` for addressable LED
* If the LED type is `LED strip`, select the backend peripheral
  * `RMT` is only available for ESP targets with RMT peripheral supported
  * `SPI` is available for all ESP targets
* Set the GPIO number used for the signal in the `Blink GPIO number` option.
* Set the blinking period in the `Blink period in ms` option.

### Build and Flash

Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

See the [Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.

## Example Output

As you run the example, you will see the LED blinking, according to the previously defined period. For the addressable LED, you can also change the LED color by setting the `led_strip_set_pixel(led_strip, 0, 16, 16, 16);` (LED Strip, Pixel Number, Red, Green, Blue) with values from 0 to 255 in the [source file](main/blink_example_main.c).

```text
I (315) example: Example configured to blink addressable LED!
I (325) example: Turning the LED OFF!
I (1325) example: Turning the LED ON!
I (2325) example: Turning the LED OFF!
I (3325) example: Turning the LED ON!
I (4325) example: Turning the LED OFF!
I (5325) example: Turning the LED ON!
I (6325) example: Turning the LED OFF!
I (7325) example: Turning the LED ON!
I (8325) example: Turning the LED OFF!
```

Note: The color order could be different according to the LED model.

The pixel number indicates the pixel position in the LED strip. For a single LED, use 0.

## Troubleshooting

* If the LED isn't blinking, check the GPIO or the LED type selection in the `Example Configuration` menu.

For any technical queries, please open an [issue](https://github.com/espressif/esp-idf/issues) on GitHub. We will get back to you soon.

## 2025-07-19 local addendum

Everyghing above looks like the original README for this example. The example has been expanded to read a connected DS18B20 sensor. At present I will be building it to execute on an ESP32-C3 (RISC-V). Steps to do so include"

* Original ESP tool chain installed per instructions at <https://docs.espressif.com/projects/esp-idf/en/v5.4.2/esp32/get-started/linux-macos-setup.html> (Original install was 5.4.1)
* Switch drop down upper left from ESP32 to ESP32-C3 and note need to run:

```text
cd ~/esp/esp-idf
./install.sh esp32c3
```

* Switch to code directory `cd ~/Programming/ESP32/Fun_with_ESP32/ESP-IDF/blink` (which may differ for you.)
* Source the toolchain setup script `. ~/esp/esp-idf/export.sh`
* Change the target `idf.py set-target esp32c3`
* Check the configuration `idf.py menuconfig` (Note: `set-target` seems to reset the configuration to default values.) ("Example Configuration" -> "Blink LED type" = GPIO and "Blink GPIO number" = 8, on board blue LED.)
* build, flash and monitor - all works! The ESP comes up as `/dev/ttyACM0` on my host.
* Next: DS18B20. Presently on GPIO4 and that's used for SPI. Used for something on board like flash? Since I don;t know and there are other options, I'll use something else. GPIO10 may be otherwise unused. (See <https://dl.artronshop.co.th/ESP32-C3%20SuperMini%20datasheet.pdf> "Pin Use.)
* Power the DS18B20 from '3V3', data to '10' and Ground to 'G'. 3.9K pullup (could not find 4.7K.)
* Change `EXAMPLE_ONEWIRE_BUS_GPIO` to 10, build, flash and monitor.
* Recognizes DS18B20 and reads the temperature.
