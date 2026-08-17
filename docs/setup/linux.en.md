# CMathMath on Linux

[Home](../../README.md) · [Español](linux.es.md) · [Windows](windows.en.md) · [macOS](macos.en.md)

## Requirements

- Git
- CMake 3.10 or newer
- A C++17-compatible compiler such as GCC or Clang
- Internet access during the first configuration so CMake can download doctest

On Ubuntu or Debian:

```sh
sudo apt update
sudo apt install git cmake build-essential
```

On Fedora:

```sh
sudo dnf install git cmake gcc-c++ make
```

On Arch Linux:

```sh
sudo pacman -S git cmake base-devel
```

Check the tools:

```sh
git --version
cmake --version
c++ --version
```

## Get the project

```sh
git clone https://github.com/AlejandroPuenteFragoso/CMathMath.git
cd CMathMath
```

## Configure and build

```sh
cmake -S . -B build -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

## Run all tests

```sh
ctest --test-dir build --output-on-failure
```

To display every test case and assertion:

```sh
./build/tests/cmathmath_tests --success
```

## Run the interpreter

```sh
./build/interpreter
```

Try expressions such as:

```text
2 + 3 * 4
(2 + 3) * 4
1 + 1 == 2
!false
nil == nil
```

Type `exit` to quit.

## Troubleshooting

- **CMake selects a different compiler:** configure from a fresh `build`
  directory or set `CXX` before configuring.
- **The CMake version is too old:** use packages from a current release of your
  distribution or the official CMake installer.
- **The doctest download fails:** check your internet connection and configure
  the project again.

See the [official CMake documentation](https://cmake.org/cmake/help/latest/).
