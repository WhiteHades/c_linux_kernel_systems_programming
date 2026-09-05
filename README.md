this is where i am learning c, modern c, c++, linux shell scripting and internals, systems and kernel programming, and cybersecurity through exercises and projects.

## start a book

open the book's folder with `nvim .` in your usual tmux session. edit in lazyvim and run commands in another pane or `:terminal`. its readme says where to write your code and how to run it.

read a section, try it, and check the result. on a fresh clone, run `mise trust`, then `mise run setup` once. use `mise run verify` to check the tools.

## book dashboard

follow the [full curriculum](https://github.com/WhiteHades/curriculum-audit/blob/main/CURRICULUM.md) for reading order and prerequisites. keep one main book active. the checks below ran during setup on 2026-09-05; they don't mean every later exercise has been completed.

| book and setup | practice | verified |
| --- | --- | --- |
| [common-sense python dsa](https://github.com/WhiteHades/leetcode_practice/tree/main/common_sense_dsa) | exercises in volumes 1 and 2 | 32 author test files |
| [modern c, 3rd edition](02_modern_c/) | exercises and longer challenges | author's binaries target and c23 starter |
| [introducing c++](03_introducing_cpp/) | chapter exercises | starter and multi-file examples |
| [crafting interpreters](crafting_interpreters/) | build jlox, then clox; chapter challenges | 485 author interpreter tests; learner builds |
| [the little book about os development](little_os_book/) | one growing x86 os project | bootable iso and terminal emulator |
| [linux kernel programming, 2nd edition](linux_kernel_programming/) | questions and labs | 37 module build targets; guest boot and module load |
| [bare-metal embedded c programming](bare_metal_embedded_c/) | firmware and peripheral projects | 10 author firmware builds; no board test |
| [python machine learning](05_hands_on_ml_py/) | chapter code and experiments | imports in all 4 dependency profiles |
| [deep learning with python, 3rd edition](https://github.com/WhiteHades/ml_engineering/tree/main/deep_learning_with_python) | notebook examples and own python files | jax, tensorflow and pytorch gpu training |
| [c++ machine learning](04_hands_on_ml_cpp/) | worked examples through chapter 14 | chapter 1 build and eigen execution |
| [programming massively parallel processors](programming_massively_parallel_processors/) | exercises, labs and a final gpu project | cuda kernel on the real gpu |
| [networking all-in-one, 9th edition](networking_all_in_one/) | follow the reference procedures | isolated dns, ping, http and packet capture |

the two older ml setups retain compatibility versions. embedded work needs the author's board; some networking sections need windows, cloud accounts or equipment. missing publisher files and gpu memory limits are listed in the affected book readmes.

builds reuse compiler caches. one repeated c++ build took 0.13 seconds after a 2.1-second uncached build; this measures compilation, not program speed.

book texts, publisher downloads, datasets, model weights, vm disks, and container state stay local. git tracks setup files, short readmes, existing licensed examples, and my code. host tools use official omarchy commands; book dependencies run in docker.

## other references

the books guiding this repository are:

- [c programming: a modern approach, second edition](https://knking.com/books/c2/) by k. n. king
- [tiny c projects](https://www.manning.com/books/tiny-c-projects) by dan gookin
- [modern c, third edition](https://www.manning.com/books/modern-c-third-edition) by jens gustedt
- [introducing c++](https://www.oreilly.com/library/view/introducing-c/9781098178130/) by frances buontempo
- [the linux command line, second edition](https://nostarch.com/releases/LinuxCommandLine2ndEdition_PR.html) by william shotts
- [the ultimate linux shell scripting guide](https://www.packtpub.com/en-us/product/the-ultimate-linux-shell-scripting-guide-9781835463154) by donald a. tevault
- [linux pocket guide, fourth edition](https://www.oreilly.com/library/view/linux-pocket-guide/9781098157951/) by daniel j. barrett
- [how linux works, third edition](https://nostarch.com/howlinuxworks3) by brian ward
- [linux system programming, second edition](https://www.oreilly.com/library/view/linux-system-programming/9781449341527/) by robert love
- [the linux programming interface](https://man7.org/tlpi/) by michael kerrisk
- [linux kernel programming, second edition](https://www.packtpub.com/en-us/product/linux-kernel-programming-9781803232225) by kaiwan n. billimoria
- [linux basics for hackers, second edition](https://nostarch.com/linux-basics-hackers-2nd-edition) by occupytheweb
- [learning kali linux, second edition](https://www.oreilly.com/library/view/learning-kali-linux/9781098154127/) by ric messier
- [the ultimate kali linux book, third edition](https://www.packtpub.com/en-gb/product/the-ultimate-kali-linux-book-9781835085806) by glen d. singh
- [hacking and security: the comprehensive guide to penetration testing and cybersecurity](https://www.sap-press.com/hacking-and-security_5696/)
- [mastering linux security and hardening, third edition](https://www.oreilly.com/library/view/mastering-linux-security/9781837630516/) by donald a. tevault
