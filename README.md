# CMathMath

[![Tests](https://github.com/AlejandroPuenteFragoso/CMathMath/actions/workflows/tests.yml/badge.svg)](https://github.com/AlejandroPuenteFragoso/CMathMath/actions/workflows/tests.yml)

Intérprete de expresiones matemáticas escrito en C++.

## Compilar y ejecutar los tests

```sh
cmake -B build -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```
