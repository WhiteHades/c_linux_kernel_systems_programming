# bare-metal embedded c programming

read the book in calibre. keep your working copy in `exercises/`.

```sh
cd ~/Codes/learning/c_linux_kernel_systems_programming/bare_metal_embedded_c
nvim .
mise run setup
```

read chapters 1 to 18 in order. the author expects general c knowledge. copy
one chapter project, type the register code, build it, and test it on the
NUCLEO-F411RE board.

```sh
mkdir -p exercises/ch05
cp -a code/Chapter5/4_Makefiles/. exercises/ch05/
mise run build -- exercises/ch05
mise run run -- exercises/ch05
mise run shell
mise run verify
```

the author projects are in `code/` at the pinned upstream revision. copy the
project for the chapter into a new `exercises/chNN/` folder before editing it.
docker provides the gnu arm compiler and openocd. a physical board, jumper
wires, a 10 kΩ potentiometer, an ADXL345 sensor, and a serial terminal are
needed for hardware exercises.
`mise run run` reports the firmware file; it does not run or flash it.

book text stays local and ignored by git. edit the source normally in lazyvim.
