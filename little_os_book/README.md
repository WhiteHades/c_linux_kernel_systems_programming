# the little book about os development

read the book in calibre and work in `exercises/`.

```sh
cd ~/Codes/learning/c_linux_kernel_systems_programming/little_os_book
nvim .
mise run setup
```

read chapters 1 to 14 in order. this is one progressive os project. type each
small step in `exercises/`, build it, boot it in the emulator, and keep the
next change small. the book expects comfort with linux, systems programming,
c, assembly, and hexadecimal notation.

```sh
mise run build
mise run run
mise run shell
mise run verify
```

the book uses gcc, nasm, make, grub, `genisoimage`, and bochs for x86/ia-32.
qemu runs the os in the terminal. press alt+2, type `q`, and press enter to
quit; press alt+1 to return to the os screen. the image supplies grub's legacy
stage2 bootloader; a local copy may be kept in `code/author/`.

book text stays local and ignored by git. the project uses docker through mise;
edit ordinary files in lazyvim. os images and kernel code run in the container.
