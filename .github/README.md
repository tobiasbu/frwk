# purpurina_frwk

Work in progress

## Packages

- core
- platform
- render

## Getting started

### Mac OS:

- Generate for Xcode

```
cmake . -B build/xcode -GXcode
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
