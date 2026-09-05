# linux kernel programming, second edition

read the book in calibre and work in `code/`.

```sh
cd ~/Codes/learning/c_linux_kernel_systems_programming/linux_kernel_programming
nvim .
mise run setup
```

read chapters 1 to 13 in order. use the supplied chapter questions. build a
module, inspect its output, and test unsafe code only in the disposable guest.

```sh
mise run build -- code/ch04/helloworld_lkm
mise run run -- code/ch06/countem.sh
mise run shell
mise run verify
```

the author targets a 6.1 lts linux guest and also documents raspberry pi 4.
the current qemu guest uses ubuntu's 7.0 kernel and 2 gib of ram. check
`uname -r` when a version matters. the companion code includes build fixes for
current kernel apis. `mise run run` and `mise run shell` boot qemu with files at
`/workspace/code`. one-shot commands power off when they finish. leave an
interactive guest with `ctrl-a`, then `x`. load modules and run oom, lockdep,
and other unsafe tests only inside that guest.

the original author README is `code/README.upstream.md`. book text stays local
and ignored by git. edit source and answer questions normally in lazyvim.
