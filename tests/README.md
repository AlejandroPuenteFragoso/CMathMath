# Tests de CMathMath

Esqueleto de pruebas automatizadas para el proyecto. Es el punto de partida del
issue #19; los ejemplos ya funcionan y los comentarios `TODO(Alex, #N)` marcan lo
que falta por cubrir, enlazado a su issue.

## Framework

Usamos [doctest](https://github.com/doctest/doctest) (single-header). No hay que
instalar nada: CMake lo descarga con `FetchContent` al configurar.

## Cómo compilar y ejecutar

Desde la raíz del repositorio:

```bash
cmake -B build -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

O ejecutar el binario de tests directamente (salida más detallada):

```bash
./build/tests/cmathmath_tests
```

## Estructura

| Archivo               | Qué prueba                                        |
|-----------------------|---------------------------------------------------|
| `test_main.cpp`       | Genera el `main()` de doctest (no editar).        |
| `test_lexer.cpp`      | Tokenización: números, operadores, espacios.      |
| `test_parser.cpp`     | Construcción del AST y rechazo de entradas inválidas. |
| `test_evaluator.cpp`  | Resultado numérico de evaluar el AST.             |

## Cómo agregar un test

```cpp
TEST_CASE("descripción clara de lo que se prueba") {
    CHECK(expresion_a_evaluar == valor_esperado);
}
```

- `CHECK` registra el fallo y continúa; `REQUIRE` aborta el caso si falla.
- Para `double` usa `doctest::Approx(...)` y evita comparar con `==` directo.
- Para errores esperados usa `CHECK_THROWS(...)`.

## Pendientes (ver issues)

- **#15** comparación e igualdad · **#16** booleanos/nil/`!` · **#17** doble evaluación
- **#26** carácter inválido debe lanzar error · **#27** asociatividad tras renombrar reglas
