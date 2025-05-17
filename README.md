# FastLEDitor

FastLEDitor is a Arduino library that lets you upload animations created with the FastLEDitor animation creation tool directly to your board.

## Features
- Upload animations directly from the LEDitor animation creation tool
- Display the saved animations
- Save animations in the filesystem in binary format to save space
- Hotspot with a web manager to choose animations and change config (If WiFi available)

## Supported frameworks

- espressif32 - [Supported boards](https://registry.platformio.org/platforms/platformio/espressif32/boards)
- atmelavr - [Supported boards](https://registry.platformio.org/platforms/platformio/atmelavr/boards)

## Supported LED panels

- WS2812
- More coming.

## How to use

1. Install the library using PlatformIO library install tool
2. Copy the code in the [BasicUsage.ino](examples/BasicUsage.ino) in your main.cpp
3. Upload the code to your board
4. Create a data folder in the root of your projet
5. Build and upload the filesystem image

## Known bugs

- If you upload an animation after uploading the code it doesn't work because the board is still in flash mode. Solution: reboot the board and try again.