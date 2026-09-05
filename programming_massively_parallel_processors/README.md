# programming massively parallel processors, 4th edition

read after learning c and c++. open this folder with `nvim .` and write your cuda files in `exercises/`.

```sh
mise run setup                       # first installation only
mise run run -- exercises/ch02.cu     # compile and run your file
mise run shell                       # nvcc, make, cuda tools, mpi
mise run verify                      # test a real gpu kernel
```

read chapters 1 to 12 and do their exercises and labs. then use the advanced chapters while building a final gpu project, as the preface recommends. keep a cpu result to check your gpu result.

the [publisher's lab manuals](https://shop.elsevier.com/books/book-companion/9780323912310) are in `code/lab-manuals/`. its separate starter-code download currently returns 404. write the book examples in `exercises/`.

the contained [cuda 13.3.1 toolkit](https://docs.nvidia.com/cuda/cuda-toolkit-release-notes/index.html) targets the gtx 1650 ti with `sm_75`. it runs on the real gpu. its 4 gb memory limits dataset sizes; cluster and multi-gpu work needs more hardware.

book text and downloads stay local. commit your own source files. save datasets and checkpoints in `.state/`.
