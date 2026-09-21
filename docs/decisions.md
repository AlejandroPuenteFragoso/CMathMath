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

# Visitor para las operaciones del AST

Las expresiones del AST solo guardan la estructura del programa y aceptan un
`ExprVisitor`. `Interpreter` evalúa los nodos y conserva el valor del último
nodo visitado; `AstPrinter` imprime el árbol. `Parser` solo construye el AST.

Esta separación permite que el intérprete tenga estado propio cuando se añadan
variables, sin pasar un entorno por cada llamada recursiva. También evita que
la impresión dependa de una cadena de `dynamic_cast` que omitiría en silencio
un tipo de nodo nuevo. La interfaz del visitor exige implementar una visita
para cada tipo de expresión.

Se consideró mantener `eval()` en los nodos, pero obligaría a distribuir la
semántica y el futuro estado entre ellos. `std::variant` con `std::visit`
ofrecería comprobación exhaustiva, pero requeriría cambiar la propiedad de los
nodos recursivos. Un visitor virtual con retorno genérico no encaja directamente
en C++; por eso las visitas retornan `void` y cada operación guarda su resultado.

Decisión relacionada: [#53](https://github.com/AlejandroPuenteFragoso/CMathMath/issues/53).
