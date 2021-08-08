# chronotrix_frwk

_Work in progress_

Chronotrix Frwk (temporary name) provides a set of libraries in modern C++ for game development. 

The goal is to deliver the following packages:  

#### :star: platform (WIP)
  Cross-platform window management and OpenGL context creation for Windows, Mac and Linux (X11).

#### :star: graphics (WIP)
  Graphics abstraction layer across multiple renderers. Currently the focus is support Vulkan only.

#### :star: core (WIP)
  Core library that provides utilities, helpers and so on.

The idea of this project is to understand cross-platform development and learn how modern computer graphics libraries work. With that, the idea is to create a game engine and editor from scratch. 

There is still a lot to do and as I develop, old decisions end up being replaced by new ones. So I do not recommend that you use Chronotrix now, because there isn't stable release yet. 

## Development

Basic dependencies:

- git
- cmake

### Mac OS

Generate for Xcode

```
cmake . -B build/xcode -GXcode
```

### Linux

Install X11 development library:

```
sudo apt-get install libx11-dev
```

For OpenGL support:

```
sudo apt install mesa-common-dev libgl1-mesa-dev
```

## Format code

#### Mac:

Install clang-format: `brew install clang-format`

```shell
./utils/format.sh src include
```

#### Windows CMD:

```
utils\format.sh src include
```
