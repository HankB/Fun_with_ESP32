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

This produices an empty `main()` that builds and flashes w/out difficulty.