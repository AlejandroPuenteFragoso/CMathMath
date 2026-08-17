# CMathMath on Windows

[Home](../../README.md) · [Español](windows.es.md) · [macOS](macos.en.md) · [Linux](linux.en.md)

This guide uses PowerShell and works with Visual Studio/MSVC. You can also use
Ninja when it is already installed and configured.

## Requirements

- Git
- CMake 3.10 or newer
- Visual Studio or Build Tools with the **Desktop development with C++** workload
- Internet access during the first configuration so CMake can download doctest

Check the tools:

```powershell
git --version
cmake --version
```

## Get the project

```powershell
git clone https://github.com/AlejandroPuenteFragoso/CMathMath.git
cd CMathMath
```

If you already have the repository, open PowerShell in its root directory.

## Configure and build

```powershell
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --config Debug
```

## Run all tests

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

To display every test case and assertion:

```powershell
.\build\tests\Debug\cmathmath_tests.exe --success
```

When using Ninja, the test executable may be located at
`.\build\tests\cmathmath_tests.exe`.

## Run the interpreter

With the Visual Studio generator:

```powershell
.\build\Debug\interpreter.exe
```

With Ninja:

```powershell
.\build\interpreter.exe
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

- **No compiler is found:** open a *Developer PowerShell for VS* or install the
  C++ workload from Visual Studio Installer.
- **CMake reuses the wrong configuration:** delete only the `build` directory
  and configure the project again.
- **The doctest download fails:** check your internet connection and configure
  the project again.

See the official documentation for
[MSVC Build Tools](https://learn.microsoft.com/cpp/overview/acquire-msvc) and
[CMake](https://cmake.org/download/).
