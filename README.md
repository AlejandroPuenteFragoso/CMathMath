# CMathMath

[![Tests](https://github.com/AlejandroPuenteFragoso/CMathMath/actions/workflows/tests.yml/badge.svg)](https://github.com/AlejandroPuenteFragoso/CMathMath/actions/workflows/tests.yml)

**Español:** intérprete de expresiones escrito en C++17 para aprender cómo se
construyen un lexer, un parser de descenso recursivo y un árbol de sintaxis
abstracta (AST).

**English:** a C++17 expression interpreter built to explore lexing,
recursive-descent parsing, abstract syntax trees (ASTs), and evaluation.

## Guías de instalación / Setup guides

Elige tu sistema operativo e idioma. Choose your operating system and language.

| Sistema / Platform | Español | English |
|---|---|---|
| Windows | [Guía para Windows](docs/setup/windows.es.md) | [Windows guide](docs/setup/windows.en.md) |
| macOS | [Guía para macOS](docs/setup/macos.es.md) | [macOS guide](docs/setup/macos.en.md) |
| Linux | [Guía para Linux](docs/setup/linux.es.md) | [Linux guide](docs/setup/linux.en.md) |

## Funcionalidad / Features

- Operaciones aritméticas / Arithmetic: `+`, `-`, `*`, `/`
- Operadores unarios / Unary operators: `+`, `-`, `!`
- Comparación / Comparison: `<`, `<=`, `>`, `>=`
- Igualdad / Equality: `==`, `!=`
- Literales / Literals: numbers, `true`, `false`, `nil`
- Agrupación y precedencia / Grouping and precedence with parentheses
- Errores léxicos, sintácticos y de ejecución / Lexer, parser, and runtime errors
- Pruebas automatizadas con doctest y CTest / Automated tests with doctest and CTest

## Inicio rápido / Quick start

Ejecuta los comandos desde la raíz del repositorio con CMake y un compilador
compatible con C++17. Run these commands from the repository root with CMake
and a C++17-compatible compiler.

### Ejecutar el programa / Run the program

**1. Configurar / Configure.** Genera los archivos de compilación dentro de
`build`. This generates the build files inside `build`.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

**2. Compilar / Build.** Compila el ejecutable `interpreter` en modo Debug.
This builds the `interpreter` executable in Debug mode.

```sh
cmake --build build --config Debug
```

**3. Iniciar / Start.** Ejecuta el intérprete interactivo. This starts the
interactive interpreter.

Windows con Visual Studio / Windows with Visual Studio:

```powershell
.\build\Debug\interpreter.exe
```

Windows con Ninja / Windows with Ninja:

```powershell
.\build\interpreter.exe
```

macOS y Linux / macOS and Linux:

```sh
./build/interpreter
```

### Ejecutar las pruebas / Run the tests

**1. Habilitar las pruebas / Enable tests.** Configura el proyecto con
`BUILD_TESTING` para incluir la suite de doctest. This configures the project
with `BUILD_TESTING` so the doctest suite is included.

```sh
cmake -S . -B build -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug
```

La primera configuración con pruebas necesita conexión a internet para
descargar doctest. The first test configuration requires internet access to
download doctest.

**2. Compilar / Build.** Compila tanto el intérprete como el ejecutable de
pruebas. This builds both the interpreter and the test executable.

```sh
cmake --build build --config Debug
```

**3. Probar / Test.** Ejecuta todos los casos registrados y muestra los detalles
si alguno falla. This runs every registered test and prints details when a test
fails.

```sh
ctest --test-dir build -C Debug --output-on-failure
```

## Ejemplos / Examples

```text
2 + 3 * 4       → 14
(2 + 3) * 4     → 20
1 + 1 == 2      → true
!false          → true
nil == nil      → true
```

Escribe `exit` para cerrar el intérprete. Type `exit` to close the interpreter.

## Estructura / Project structure

```text
src/lexer/      Tokenización / Tokenization
src/parser/     Parser de descenso recursivo / Recursive-descent parser
src/ast/        Nodos y evaluación del AST / AST nodes and evaluation
src/runtime/    Valores en tiempo de ejecución / Runtime values
src/main/       REPL de consola / Console REPL
tests/          Pruebas automatizadas / Automated tests
docs/           Gramática, decisiones y documentación / Grammar and documentation
```

## Contribuir / Contributing

Antes de enviar un pull request, compila el proyecto y ejecuta toda la suite.
Before opening a pull request, build the project and run the complete test suite.

La configuración y ejecución de pruebas siguen el flujo estándar de
[CMake](https://cmake.org/cmake/help/latest/manual/cmake.1.html) y
[CTest](https://cmake.org/cmake/help/latest/manual/ctest.1.html).
