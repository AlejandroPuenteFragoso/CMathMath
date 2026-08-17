# Valores y truthiness

Los valores evaluados se representan con `Value`, una variante que puede contener
un número, un booleano o `nil`.

La regla de *truthiness* sigue a Lox:

- `false` y `nil` son falsos.
- `true` es verdadero.
- Todos los números son verdaderos, incluido `0`.

El operador `!` devuelve la negación de esa regla. Las operaciones aritméticas y
las comparaciones de orden requieren operandos numéricos; la igualdad permite
comparar cualquier par de valores.
