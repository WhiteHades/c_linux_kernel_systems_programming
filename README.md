this is where i am learning c, modern c, linux, linux internals, and linux systems programming through one connected path.

## path

1. `01_c_programming_a_modern_approach` builds the c foundation.
2. `02_tiny_c_projects` turns that foundation into practical programs.
3. `03_modern_c` revisits the language through modern c and c23.
4. `04_linux_the_comprehensive_guide` builds practical linux knowledge.
5. `05_how_linux_works` goes deeper into how linux works internally.
6. `06_the_linux_programming_interface` connects c and linux through system calls and operating system interfaces.

each part builds on the one before it, and code is added only as i reach that part of the path.

## tmux workflow

running bare `tmux` from any numbered book directory, or one of its subdirectories, opens a session named after that book directory. a new session starts with two top-and-bottom panes in the current directory; later invocations reuse the existing session without changing its panes.

the behavior is fully contained in this repository. `mise.toml` puts the tracked `tmux/commands/tmux` wrapper first on `PATH`; the wrapper delegates managed sessions to `tmux/tmux-learning-session` and leaves all other tmux commands unchanged. after cloning, run `mise trust`. `tests/test-tmux-learning-session` verifies all six directories on an isolated tmux socket.

## books

1. [c programming a modern approach second edition](https://knking.com/books/c2/) by k. n. king
2. [tiny c projects](https://www.manning.com/books/tiny-c-projects) by dan gookin
3. [modern c third edition](https://www.manning.com/books/modern-c-third-edition) by jens gustedt
4. [linux the comprehensive guide](https://www.sap-press.com/linux_5779/) by michael kofler
5. [how linux works third edition](https://nostarch.com/howlinuxworks3) by brian ward
6. [the linux programming interface](https://man7.org/tlpi/) by michael kerrisk
