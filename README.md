# Solis VCU

Vehicle control unit is responsible to process inputs from solar car's driver, to persistently store offline CAN data, and to send realtime CAN data to strategy unit.

## Requirements

This project is configured with targets STM32F303CB, STM32F103RB (arch=arm32). To install ARM32 toolchain follow instructions for your specific OS:

_NOTE 1:_ Commands that start with `$` should be executed from the CLI.

_NOTE 2:_ Certain commands require administrator privileges, so `sudo` might need to be prepended (Ex.: `$ sudo apt update`).

_NOTE 3:_ WSL2 distors are also supported.

### Debian/Ubuntu

Install system requirements:

```
$ apt update
$ apt install build-essential \
  cmake \
  git \
  python3 \
  pyhton3-pip \
  pyhton3-venv \
  gcc-arm-none-eabi \
  gdb-arm-none-eabi \
  binutils-arm-none-eabi \
  newlib
```

Clone repository, configure and activate virtual environment:

```
$ git clone https://github.com/SolisEV-UTCN/vehicle_control_unit.git vcu
$ cd vcu
$ python3 -m venv .venv
$ source .venv/bin/activate
```

### Arch

Install system requirements:

```
$ pacman -Sy
$ pacman -Sy build-essential \
  cmake \
  git \
  python3 \
  pyhton3-pip \
  pyhton3-venv \
  gcc-arm-none-eabi \
  g++-arm-none-eabi \
  arm-none-eabi-binutils \
  arm-none-eabi-gcc \
  arm-none-eabi-gdb \
  arm-none-eabi-newlib
```

Clone repository, configure and activate virtual environment:

```
$ git clone https://github.com/SolisEV-UTCN/vehicle_control_unit.git vcu
$ cd vcu
$ python3 -m venv .venv
$ source .venv/bin/activate
```

### Windows (WIP)

Install system requirements:

```
#TODO
```

Clone repository, configure and activate virtual environment:

```
$ git clone https://github.com/SolisEV-UTCN/vehicle_control_unit.git vcu
$ cd vcu
$ python3 -m venv .venv
$ & .venv\Scripts\activate
```

### Mac

1. Installing Homebrew on macOS

Installation Steps:

Run the following command to install Homebrew:

```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

Verify Homebrew installation:

```
brew --version
```

Add Homebrew to your PATH (if not done automatically):

```
echo 'export PATH="/opt/homebrew/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

2. Installing Packages Using Homebrew

Run the following command in Terminal to install all packages:

```
brew install cmake arm-none-eabi-gcc arm-none-eabi-binutils
```

Clone repository, configure and activate virtual environment:

```
$ git clone https://github.com/SolisEV-UTCN/vehicle_control_unit.git vcu
$ cd vcu
$ python3 -m venv .venv
$ source .venv/bin/activate
```

## Configurations

Substitute `<BUILD_TYPE>` with one of following options: 
1. Release
2. Debug
3. MinSizeRel
4. RelWithDebInfo

Substitute `<TARGET>` with one of following options: 
1. stm32f103rb
2. stm32f303cb

## Building with Docker

Make sure you have a docker installed and running. Docker will mount a local volume to output generated files.

```
$ docker build . -t stm32 -f dev/dockerfile
$ docker run -v $(pwd)/build:/build -e BUILD_TYPE=<BUILD_TYPE> -e TARGET=<TARGET> stm32
```

## Building with Conan

Project dependencies are managed by _Conan_. To install and configure _Conan_:

_NOTE:_ Commands that start with `(.venv)$` should be executed from the virtual environment CLI.

```
(.venv)$ python3 -m pip install conan
(.venv)$ conan remote add libhal-trunk https://libhal.jfrog.io/artifactory/api/conan/trunk-conan
(.venv)$ conan config install -sf profiles/baremetal/v2 https://github.com/libhal/conan-config.git
(.venv)$ conan profile detect --force
```

### Using script

```
$ scripts/build.sh -b <BUILD_TYPE> -t <TARGET>
```

### Using CMake

```
(.venv)$ conan install . -pr dev/gcc-target-<TARGET>.txt --build=missing -s build_type=<BUILD_TYPE>
(.venv)$ cd build/<BUILD_TYPE>
$ cmake -GNinja -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=<BUILD_TYPE> ../..
$ cmake --build . --clean-first
```

## Flashing

__DO NOT FLASH DEVICES UNLESS YOU KNOW WHAT YOU DO__

Flashing of the device is done after building target binaries. To flash the target install following system packages:

* libusb
* ST-Link
* OpenOCD (only for debugging)

Connect target with a ST-Link/JTAG connector. Check if device is recognized by your system. `$ st-link --probe`, this will generate information about your device. For STM32F103 Nucleo board I get following output:
```
Found 1 stlink programmers
  version:    V2J33S25
  serial:     066CFF545589564867125526
  flash:      131072 (pagesize: 1024)
  sram:       20480
  chipid:     0x410
  dev-type:   STM32F1xx_MD
```

Finally, flash target `.bin` file onto FLASH memory.

`$ st-flash --reset write build/Debug/stm32f303cb/vehicle_control_unit.bin 0x08000000`

_Note 1:_ If your device-type is unknown or you can't connect to SWD check ST-Link jumpers on the board. Also, make sure JP5 jumper is set on U5V.

_Note 2:_ If you receive usb.c ERROR try using `sudo`.

_NOTE 3:_ If using WSL2, you need to pass USB device from host computer. For Windows you can use [usbipd](https://github.com/dorssel/usbipd-win). Run as administrator following PowerShell commands:

`> usbipd list` this will output all connected devices. I got following output:

```
Connected:
BUSID  VID:PID    DEVICE                                                        STATE
1-3    0483:374b  ST-Link Debug, USB Mass Storage Device, STMicroelectronic...  Not shared
1-14   8087:0026  Intel(R) Wireless Bluetooth(R)                                Not shared
2-1    17ef:609b  USB Input Device                                              Not shared
2-3    0d8c:013c  USB PnP Sound Device, USB Input Device                        Not shared
```

ST-Link on my computer was mounted with bus ID of 1-3. Next you need to make this bus shared, to do so run following command:

`> usbipd bind -b 1-3`

To verify if binding was succesfull you can rerun list command. Device should be now shared, see example below:

```
Connected:
BUSID  VID:PID    DEVICE                                                        STATE
1-3    0483:374b  ST-Link Debug, USB Mass Storage Device, STMicroelectronic...  Shared
1-14   8087:0026  Intel(R) Wireless Bluetooth(R)                                Not shared
2-1    17ef:609b  USB Input Device                                              Not shared
2-3    0d8c:013c  USB PnP Sound Device, USB Input Device                        Not shared
```

Afterwards, you can attach this device to your WSL2 instance:

`> usbipd attach -w -b 1-3`

### Debugging

Debugging is done via OpenOCD and arm-none-eabi-gdb. For more information on how to debug with GDB you can read this [summary](https://jacobmossberg.se/posts/2017/01/17/use-gdb-on-arm-assembly-program.html).

1. Open OpenOCD: `$ openocd -f /usr/share/openocd/scripts/interface/stlink.cfg -f /usr/share/openocd/scripts/target/<TARGET_CONF>.cfg`
2. Start GDB with target ELF file: `$ arm-none-eabi-gdb build/<BUILD_TYPE>/<TARGET>/vehicle_control_unit`
3. Specify source directories: `(gdb) dir <PATH_TO_REPO>/src`
4. Connect to target: `(gdb) target extended-remote localhost:3333`

_Note 1:_ Target configs (__TARGET_CONF__) is either `stm32f1x` or `stm32f3x`.

_Note 2:_ Commands that start with `(gdb)` should be executed from the GDB terminal.
