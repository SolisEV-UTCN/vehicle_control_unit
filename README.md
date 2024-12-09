# Solis VCU

Vehicle control unit is responsible to process inputs from solar car's driver, to persistently store offline CAN data, and to send realtime CAN data to strategy unit.

## Requirements

This project is configured with target STM32F103RB (arch=arm32). To install ARM32 toolchain follow instructions for your specific OS:

_NOTE 1:_ Commands that start with `$` should be executed from the CLI.

_NOTE 2:_ Certain commands require administrator privileges, so `sudo` might need to be prepended (Ex.: `$ sudo apt update`).

_NOTE 3:_ WSL2 distors are also supported.

### Debian/Ubuntu

Install system requirements:

```
$ apt update
$ apt install build-essential \
  cmake \
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
$ git clone <TODO_CHANGE_ONCE_UPLOADED> vcu
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
$ git clone <TODO_CHANGE_ONCE_UPLOADED> vcu
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
$ git clone <TODO_CHANGE_ONCE_UPLOADED> vcu
$ cd vcu
$ python3 -m venv .venv
$ & .venv\Scripts\activate
```

### Mac (WIP)

Install system requirements:

```
#TODO
```

Clone repository, configure and activate virtual environment:

```
$ git clone <TODO_CHANGE_ONCE_UPLOADED> vcu
$ cd vcu
$ python3 -m venv .venv
$ source .venv/bin/activate
```

## Building

Project dependencies are managed by _Conan_. To install and configure _Conan_:

_NOTE:_ Commands that start with `(.venv)$` should be executed from the virtual environment CLI.

```
(.venv)$ python3 -m pip install conan
(.venv)$ conan remote add libhal-trunk https://libhal.jfrog.io/artifactory/api/conan/trunk-conan
```

There are 4 __BUILD_TYPES__: 
1. Release (default)
2. Debug
3. MinSizeRel
4. RelWithDebInfo

```
(.venv)$ conan install . -pr dev/gcc-target.txt --build=missing -s build_type=<BUILD_TYPE>
(.venv)$ cd build/<BUILD_TYPE>
$ cmake -GNinja -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=<BUILD_TYPE> ../..
$ cmake --build . --clean-first
```

## Flashing
