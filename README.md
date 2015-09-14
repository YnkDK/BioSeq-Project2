# Algorithms in Bioinformatics - Sequences Q1/2015
### By Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
This project is about implementing and experimenting with pairwise sequence comparison methods to compute optimal
global alignments of two sequences where the object is to minimize a cost.

# How to compile
This project depends on `cmake` version 3.2 and is only tested on Ubuntu 14.04. To get the latest `cmake` run
the following:

```bash
sudo add-apt-repository ppa:george-edison55/cmake-3.x
sudo apt-get update
```

If `cmake` is already installed, use: `sudo apt-get upgrade`, otherwise use `sudo apt-get install cmake`

To compile all sources, run `./make.sh` (or the usual `cmake` command, the bash scripts ensures uniformity).

The main found is now located in `build/bin`.

# How to run a single algorithm

./executable [all,global_linear,global_affine] seq1 seq2

Available algorithms: `global_linear`, `global_affine`