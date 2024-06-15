# Raspberry Pi Pico Thermostat

![High Level Diagram](documentation/thermostat-C1.svg)


[![Tests on Host and Target](https://github.com/whatisbyandby/rp-pico-thermostat/actions/workflows/cmake.yml/badge.svg)](https://github.com/whatisbyandby/rp-pico-thermostat/actions/workflows/cmake.yml)

- [Raspberry Pi Pico Thermostat](#raspberry-pi-pico-thermostat)
  - [Project Summary](#project-summary)
  - [Hardware](#hardware)
    - [Hardware Summary](#hardware-summary)
  - [Firmware](#firmware)
    - [Firmware Summary](#firmware-summary)
    - [Installation](#installation)
    - [Development](#development)
      - [Before you start](#before-you-start)
      - [Preparing your build environment](#preparing-your-build-environment)
      - [Grab the Pimoroni libraries](#grab-the-pimoroni-libraries)
      - [Clone this project](#clone-this-project)
      - [Prepare Visual Studio Code](#prepare-visual-studio-code)



## Project Summary 
The purpose of this project is to create an open-source and privacy focused smart thermostat. I plan to use this with Home Assistant's MQTT HVAC integration [MQTT HVAC](https://www.home-assistant.io/integrations/climate.mqtt/). I found it difficult to find smart home devices that I was excited to use, especially thermostats. Currently this project in only targeting the Raspberry Pi Pico W using the C/C++ SDK, but I could see this being ported to other platforms in the future.

## Hardware

![Hardware High Level Diagram](documentation/hardware/thermostat-hardware-C2.svg)

### Hardware Summary

The hardware is still very early in development, and I'm currently using the Pimoroni Pico Explorer Base as a development platform [Pico Explorer](https://shop.pimoroni.com/products/pico-explorer-base?variant=32369514315859). The Pico Explorer Base has a 240x240 LCD display, 4 buttons, and a small breadboard where I have used LEDs to represent the outputs to the relays, and is a reasonable stand in for the harware for now. I plan to design and manufacture a custom PCB, that will act as a carrier board for the Pico W. The first iteration of the board will support a basic 4 wire HVAC system, with the ability to control a furnace, air conditioner, and fan. The board will have 3 relays to control the Furnace, Fan, and AC. The board will also have a temperature and humidity sensor to monitor the environment. I've currently chosen the AHT20, but I haven't decided if it should be part of the board, or if it's better to allow the user to choose their own sensor, and just provide an I2C connector.
I plan to power the board via the standard 16-24 VAC used for HVAC control circuits, and will convert the AC - DC to power the pico using a full wave rectifier. There will be a DC section of the board to power the MCU and periperals, and an AC section that will be used to power the load side of the control relays.

## Firmware

![Software High Level Diagram](documentation/software/thermostat-software-C2.svg)

### Firmware Summary

The firware is written in C++ but I chose to avoid features like runtime polymorphism, exceptions, and templates to keep the code simple and efficient. I also chose to avoid dynamic memory allocation. The firmware is designed to be decoupled from any one particular target, and uses compile time linking to target the platform specific code. The firmware uses both cores on the RP2040, where Core 0 runs the main loop for the thermostat, monitoring the temperature, checking the current state of the world, then issusing request to turn on or off the HVAC components, and finally updating the display and publishing the current state of the thermostat. Core 1 handles monitoring inputs from the physical UI, the UART interterface, and incomming command from the MQTT subscriber.  I wanted the code to be easily testable on the host machine, and took much of lessons from the book [Test Driven Development in Embedded C](https://pragprog.com/titles/jgade/test-driven-development-for-embedded-c/) when structuring the tests. I plan to use the Pimoroni Pico libraries for interfacing with the display, to avoid reinventing the wheel.

### Installation

The firmware can be installed using the normal Pico USB boot process. Hold down the boot button while plugging in the USB cable. The Pico will appear as a USB drive. Drag and drop the UF2 file onto the drive.

### Development

#### Before you start

It's easier if you make a `pico` directory or similar in which you keep the SDK, Pimoroni Libraries and your projects alongside each other. This makes it easier to include libraries.

#### Preparing your build environment

Install build requirements:

```sh
sudo apt update
sudo apt install cmake gcc-arm-none-eabi build-essential
```

And the Pico SDK:

```sh
git clone https://github.com/raspberrypi/pico-sdk
cd pico-sdk
git submodule update --init
export PICO_SDK_PATH=`pwd`
cd ../
```

The `PICO_SDK_PATH` set above will only last the duration of your session.

You should should ensure your `PICO_SDK_PATH` environment variable is set by `~/.profile`:

```sh
export PICO_SDK_PATH="/path/to/pico-sdk"
```

#### Grab the Pimoroni libraries

```sh
git clone https://github.com/pimoroni/pimoroni-pico
```

#### Clone this project

```sh
git clone https://github.com/pimoroni/pico-boilerplate
cd pico-boilerplate
```

If you have not or don't want to set `PICO_SDK_PATH` you can edit `.vscode/settings.json` to pass the path directly to CMake.

#### Prepare Visual Studio Code

Open VS Code and hit `Ctrl+Shift+P`.

Type `Install` and select `Extensions: Install Extensions`.

Make sure you install:

1. C/C++
2. CMake
3. CMake Tools
4. Cortex-Debug (optional: for debugging via a Picoprobe or Pi GPIO)
5. Markdown All in One (recommended: for preparing your own README.md)
