# crafting interpreters

read robert nystrom's book in calibre, in order. build jlox in part ii, then
clox in part iii. complete each chapter's challenges in `exercises/`.

`code/` is the pinned official reference checkout and stays local. write your
jlox files in `exercises/jlox/` and clox files in `exercises/clox/`. build and
run use your exercises. verify and test check the reference checkout.

`setup.sh` pins commit `4a840f70f69c6ddd17cfef4f6964f8e1bcd8c3d4`.

```sh
mise run setup
mise run verify
mise run build -- jlox
mise run run -- jlox
mise run build -- clox
mise run run -- clox
```

the official test runner requires dart 2.19.6, so the container pins that
version. c and java use gcc 16 and jdk 26. generated files stay local.
