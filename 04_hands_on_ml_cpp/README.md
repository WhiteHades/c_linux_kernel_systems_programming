# hands-on machine learning with c++

open `code/` in lazyvim:

```sh
cd ~/Codes/learning/c_linux_kernel_systems_programming/04_hands_on_ml_cpp/code
nvim .
```

run this once:

```sh
mise run setup
```

then use the terminal inside neovim:

```sh
mise run build -- 1
mise run run -- Chapter01/eigen_samples/build/linalg_eigen
```

## how to study

read chapters 1 to 14 in order. read a section, type or change the matching example under `ChapterNN`, build the chapter, and run it. compare the result with the book, then finish the summary and further reading.

the repository has worked examples. the book has no separate end-of-chapter exercise set. most machine-learning code here is c++.

on a fresh checkout, `mise run setup` fetches the tested author revision into `code/` and builds the contained environment. the image keeps compatibility versions for this book's older apis.

chapter 14 is android work; `mise run build -- 14` uses its own tools. the author checkout is missing files for 1 chapter 10 target. that target needs the missing upstream files before it can build.

docker builds and runs the code. book text, datasets, models, and container state stay local. files created in `code/` belong to your normal user.

`code/` has its own git history and is ignored by the parent repository. you can commit experiments locally there, but `origin` points to the author. pushing this workspace does not back up those edits to github.
