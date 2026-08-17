# CMathMath en Linux

[Inicio](../../README.md) · [English](linux.en.md) · [Windows](windows.es.md) · [macOS](macos.es.md)

## Requisitos

- Git
- CMake 3.10 o posterior
- Un compilador compatible con C++17, como GCC o Clang
- Conexión a internet durante la primera configuración para descargar doctest

En Ubuntu o Debian:

```sh
sudo apt update
sudo apt install git cmake build-essential
```

En Fedora:

```sh
sudo dnf install git cmake gcc-c++ make
```

En Arch Linux:

```sh
sudo pacman -S git cmake base-devel
```

Comprueba las herramientas:

```sh
git --version
cmake --version
c++ --version
```

## Obtener el proyecto

```sh
git clone https://github.com/AlejandroPuenteFragoso/CMathMath.git
cd CMathMath
```

## Configurar y compilar

```sh
cmake -S . -B build -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

## Ejecutar todas las pruebas

```sh
ctest --test-dir build --output-on-failure
```

Para ver cada caso y aserción:

```sh
./build/tests/cmathmath_tests --success
```

## Ejecutar el intérprete

```sh
./build/interpreter
```

Prueba expresiones como:

```text
2 + 3 * 4
(2 + 3) * 4
1 + 1 == 2
!false
nil == nil
```

Escribe `exit` para terminar.

## Problemas comunes

- **CMake encuentra otro compilador:** configura desde una carpeta `build`
  nueva o define `CXX` antes de configurar.
- **La versión de CMake es demasiado antigua:** utiliza los paquetes de una
  versión vigente de tu distribución o el instalador oficial de CMake.
- **Falla la descarga de doctest:** verifica la conexión a internet y vuelve a
  configurar el proyecto.

Consulta la [documentación oficial de CMake](https://cmake.org/cmake/help/latest/).
