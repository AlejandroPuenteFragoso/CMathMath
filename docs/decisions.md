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

# Comparaciones encadenadas

Las reglas de comparación e igualdad aceptan como máximo un operador por nivel de
precedencia. Expresiones como `1 < 2 < 3` y `true == false == false` son errores
sintácticos. Esto evita que el resultado booleano de la primera operación se use
implícitamente como operando de la segunda.

La restricción se aplica dentro de cada subexpresión. El agrupamiento explícito y
la combinación de niveles de precedencia siguen permitidos; por ejemplo,
`(1 < 2) == true` y `1 < 2 == true` son expresiones válidas.
