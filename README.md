# Regex Word Generator

A C program that explores formal languages: given an alphabet and a regular expression, it generates words of the language the expression describes, then checks whether a given word is among them.

## Features

- User-defined alphabet (e.g. `a,b`)
- Validates that the expression only uses symbols from the alphabet
- Supported operators:
  - concatenation: `ab`
  - Kleene star on a symbol or a group: `a*`, `(ab)*`
  - union inside a group: `(a+b)`, `(a+b)*`
- Generates as many words as the user asks for (star is expanded up to 3 repetitions)
- Checks whether a word is in the generated set

## Build & Run

```bash
gcc -std=c11 -Wall regex_word_generator.c -o regex_word_generator
./regex_word_generator
```

## Example

```text
Alfabeyi giriniz (ornek: a,b): a,b,c
Duzenli ifadeyi giriniz: (a+b)*c
L dilinin kac kelimesini gormek istiyorsunuz? 10
L={c, ac, bc, aac, bac, abc, bbc, aaac, baac, abac}
Kontrol edilecek kelimeyi giriniz: abc
Bu kelime L diline aittir.
```

## How It Works

`kelimeUret` walks the expression recursively. Plain symbols are appended to the current word, `x*` branches into 0–3 copies of `x`, and a parenthesized group is split on `+` into options. For a starred group, every sequence of 1–3 options is generated. Duplicates are skipped, and generation stops once the requested number of words is reached.

## Limitations

- Union (`+`) is supported inside parentheses only
- Nested groups and nested stars are not expanded
- Membership is checked against the generated words, not with an automaton
