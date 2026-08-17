# CMathMath en Windows

[Inicio](../../README.md) · [English](windows.en.md) · [macOS](macos.es.md) · [Linux](linux.es.md)

Esta guía utiliza PowerShell y funciona con Visual Studio/MSVC. También puedes
usar Ninja si ya está instalado y configurado.

## Requisitos

- Git
- CMake 3.10 o posterior
- Visual Studio o Build Tools con la carga de trabajo **Desarrollo para el
  escritorio con C++**
- Conexión a internet durante la primera configuración para descargar doctest

Comprueba las herramientas:

```powershell
git --version
cmake --version
```

## Obtener el proyecto

```powershell
git clone https://github.com/AlejandroPuenteFragoso/CMathMath.git
cd CMathMath
```

Si ya tienes el repositorio, abre PowerShell en su carpeta raíz.

## Configurar y compilar

```powershell
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --config Debug
```

## Ejecutar todas las pruebas

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

Para ver cada caso y aserción:

```powershell
.\build\tests\Debug\cmathmath_tests.exe --success
```

Si usas Ninja, el ejecutable de pruebas puede quedar en
`.\build\tests\cmathmath_tests.exe`.

## Ejecutar el intérprete

Con el generador de Visual Studio:

```powershell
.\build\Debug\interpreter.exe
```

Con Ninja:

```powershell
.\build\interpreter.exe
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

- **No se encuentra un compilador:** abre una *Developer PowerShell for VS* o
  instala la carga de trabajo de C++ desde Visual Studio Installer.
- **CMake reutiliza una configuración incorrecta:** elimina solamente la carpeta
  `build` y vuelve a ejecutar los comandos de configuración.
- **Falla la descarga de doctest:** verifica la conexión a internet y vuelve a
  configurar el proyecto.

Consulta la documentación oficial de
[MSVC Build Tools](https://learn.microsoft.com/cpp/overview/acquire-msvc) y
[CMake](https://cmake.org/download/).
