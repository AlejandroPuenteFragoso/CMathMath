# CMathMath en macOS

[Inicio](../../README.md) · [English](macos.en.md) · [Windows](windows.es.md) · [Linux](linux.es.md)

## Requisitos

- Git
- CMake 3.10 o posterior
- Un compilador compatible con C++17, como Apple Clang
- Conexión a internet durante la primera configuración para descargar doctest

Instala las herramientas de línea de comandos de Xcode si todavía no están
disponibles:

```sh
xcode-select --install
```

Instala CMake desde [cmake.org](https://cmake.org/download/) o, si utilizas
Homebrew:

```sh
brew install cmake
```

Comprueba la instalación:

```sh
git --version
cmake --version
clang++ --version
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

- **No se encuentra el compilador:** ejecuta `xcode-select --install` y completa
  la instalación gráfica.
- **CMake no está en `PATH`:** abre una terminal nueva después de instalarlo o
  revisa las instrucciones del instalador utilizado.
- **Falla la descarga de doctest:** verifica la conexión a internet y vuelve a
  configurar el proyecto.

Consulta la guía oficial de Apple para
[instalar Command Line Tools](https://developer.apple.com/documentation/xcode/installing-the-command-line-tools/).
