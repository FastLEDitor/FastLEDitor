# FastLEDitor

FastLEDitor is a Arduino library that lets you upload animations created with the [FastLEDitor animation creation tool](https://fastleditor.github.io/FastLEDitorAnimationCreator/) directly to your board.

## Features
- Upload animations directly from the [LEDitor animation creation tool](https://fastleditor.github.io/FastLEDitorAnimationCreator/)
- Display the saved animations
- Save animations in the filesystem in binary format to save space
- Hotspot with a web manager to choose animations and change config (If WiFi available)

## Supported frameworks

- espressif32 - [Supported boards](https://registry.platformio.org/platforms/platformio/espressif32/boards)

Open an issue if you want another framework supported and I will do my best to implement it.

## Supported LED panels

- WS2812
- More coming.

## How to use

1. Install the library using PlatformIO library install tool
2. Copy the code in the [BasicUsage.ino](examples/BasicUsage.ino) in your main.cpp
3. Upload the code to your board
4. Create a data folder in the root of your projet
5. If using the web server, download the [animations.html](/data/animations.html) file and the [bootstrap](/data/bootstrap/) folder and place it in your data folder
6. Build and upload the filesystem image
7. Use the [LEDitor animation creation tool](https://fastleditor.github.io/FastLEDitorAnimationCreator/) to create and upload animations
8. Connect your led panel to your ESP32 (Default pin 17)

If you are using the webserver, you can connect to the FastLEDitor hotspot with default password 12345678 or redefine it like in the [ESP32Usage.ino](/examples/ESP32Usage.ino) to change animations and settings.

## Known bugs

- If you upload an animation after uploading the code it doesn't work because the board is still in flash mode. Solution: reboot the board and try again.