# introducing c++

read frances buontempo's book in calibre. follow chapters 1 to 15 in order.

the author's examples are in `code/`. put your exercise answers and experiments
in `exercises/`. the book uses c++23 and includes exercises.

```sh
mise run setup
mise run verify
mise run run -- code/chapter_01/hello.cpp
```

build another file with `mise run build -- code/chapter_02/input.cpp`.
for a multi-file example, pass every source, then run the same files:

```sh
mise run build -- code/chapter_05/analysis.cpp code/chapter_05/input.cpp code/chapter_05/main.cpp
mise run run -- code/chapter_05/analysis.cpp code/chapter_05/input.cpp code/chapter_05/main.cpp
```

put program arguments after `--`. use `mise run shell` when you need the
contained compiler shell. generated files stay in `.state/`; the book text
stays local and is never committed.
