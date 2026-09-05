this is where i am learning c, modern c, c++, linux shell scripting and internals, systems and kernel programming, and cybersecurity through exercises and projects.

## start a book

open the book's folder with `nvim .` in your usual tmux session. edit in lazyvim and run commands in another pane or `:terminal`. its readme says where to write your code and how to run it.

read a section, try it, and check the result. on a fresh clone, run `mise trust`, then `mise run setup` once. use `mise run verify` to check the tools.

## reading order

start after basic c, python, and shell practice. keep one main book active. the [full curriculum](https://github.com/WhiteHades/curriculum-audit/blob/main/CURRICULUM.md) covers the linux and maths background between these books.

| order | book and setup | what to do |
| --- | --- | --- |
| 1 | [common-sense python dsa](https://github.com/WhiteHades/leetcode_practice/tree/main/common_sense_dsa) | volume 1, then volume 2 |
| 2 | [modern c, 3rd edition](02_modern_c/) | c23 and deeper c practice |
| 3 | [introducing c++](03_introducing_cpp/) | modern c++ fundamentals |
| 4 | [crafting interpreters](crafting_interpreters/) | build jlox, then clox |
| 5 | [the little book about os development](little_os_book/) | build and boot an x86 os |
| 6 | [linux kernel programming, 2nd edition](linux_kernel_programming/) | kernel labs in a disposable vm |
| 7 | [bare-metal embedded c programming](bare_metal_embedded_c/) | firmware on the author's board |
| 8 | [python machine learning](05_hands_on_ml_py/) | ml foundations before deep learning |
| 9 | [deep learning with python, 3rd edition](https://github.com/WhiteHades/ml_engineering/tree/main/deep_learning_with_python) | keras models and experiments |
| 10 | [c++ machine learning](04_hands_on_ml_cpp/) | native ml libraries |
| 11 | [programming massively parallel processors](programming_massively_parallel_processors/) | cuda exercises and a final gpu project |

[networking all-in-one, 9th edition](networking_all_in_one/) goes alongside linux study. start with its networking and protocol minibooks, then use later sections when needed.

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
