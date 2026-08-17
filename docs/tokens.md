# Tokens

| Token | Lexema |
|---|---|
| `NUMBER` | Un número entero o decimal |
| `TRUE` | `true` |
| `FALSE` | `false` |
| `NIL` | `nil` |
| `PLUS` | `+` |
| `MINUS` | `-` |
| `STAR` | `*` |
| `SLASH` | `/` |
| `BANG` | `!` |
| `EQUAL_EQUAL` | `==` |
| `BANG_EQUAL` | `!=` |
| `LESS` | `<` |
| `LESS_EQUAL` | `<=` |
| `GREATER` | `>` |
| `GREATER_EQUAL` | `>=` |
| `LPAREN` | `(` |
| `RPAREN` | `)` |
| `EOF_TOKEN` | Fin de la entrada |

Por ejemplo, la entrada `!false == true` produce:

```text
BANG
FALSE
EQUAL_EQUAL
TRUE
EOF_TOKEN
```
