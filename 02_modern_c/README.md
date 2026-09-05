# modern c

read jens gustedt's book in calibre and follow its chapters in order. use the
author's examples in `code/`, then put your own exercises in `exercises/`.
the book includes exercises and longer challenges; keep your answers in
`exercises/`.

the book uses modern c, including c23. `code/c23-fallback.h` helps when an
example needs an older compiler mode.

```sh
mise run setup
mise run verify
mise run run -- code/getting-started.c
```

build an author target with `mise run build -- binaries`. use `mise run shell`
for the contained compiler shell. generated files stay in `.state/`; the book
text stays local and is never committed.

the author's full binaries target uses its default `-O3` mode. with `OPT=-O0`,
inline examples such as `euclid` and `stats` may fail to link.
