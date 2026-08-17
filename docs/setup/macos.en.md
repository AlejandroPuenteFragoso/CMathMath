# CMathMath on macOS

[Home](../../README.md) · [Español](macos.es.md) · [Windows](windows.en.md) · [Linux](linux.en.md)

## Requirements

- Git
- CMake 3.10 or newer
- A C++17-compatible compiler such as Apple Clang
- Internet access during the first configuration so CMake can download doctest

Install the Xcode command-line tools if they are not available yet:

```sh
xcode-select --install
```

Install CMake from [cmake.org](https://cmake.org/download/) or, when using
Homebrew:

```sh
brew install cmake
```

Check the installation:

```sh
git --version
cmake --version
clang++ --version
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

- **No compiler is found:** run `xcode-select --install` and complete the system
  installation dialog.
- **CMake is not in `PATH`:** open a new terminal after installing it or review
  the instructions from the installer you used.
- **The doctest download fails:** check your internet connection and configure
  the project again.

See Apple's official guide to
[install the command-line tools](https://developer.apple.com/documentation/xcode/installing-the-command-line-tools/).
