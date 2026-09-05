# machine learning with pytorch and scikit-learn

open `code/` in lazyvim:

```sh
cd ~/Codes/learning/c_linux_kernel_systems_programming/05_hands_on_ml_py/code
nvim .
```

run this once:

```sh
mise run setup
```

then use the terminal inside neovim:

```sh
mise run run -- ch02/ch02.py  # run a python chapter file
mise run lab -- 02            # open the chapter notebooks
```

## how to study

read chapters 1 to 19 in order. chapter 1 explains the setup; coding starts in chapter 2. read a section, then open the matching `chNN` notebook or python file. run it in small pieces, change it, and compare the result with the book. check each chapter's `README.md` for author corrections.

use the notebooks alongside the book's explanations and maths. exercises appear in the prose rather than in a separate exercise directory.

on a fresh checkout, `mise run setup` fetches the tested author revision into `code/` and builds the contained environment. the image keeps compatibility versions for this book's older apis.

book text, datasets, models, and container state stay local. files created in `code/` belong to your normal user.

`code/` has its own git history and is ignored by the parent repository. you can commit experiments locally there, but `origin` points to the author. pushing this workspace does not back up those edits to github.
