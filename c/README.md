# C

This directory contains C implementations of various S4TK functions, including:
- UInt parsing methods from [BinaryDecoder](https://sims4toolkit.com/#/docs/encoding/0.1.4/classes/BinaryDecoder) in `encoding.h`
- [Binary STBL parser](https://github.com/sims4toolkit/models/blob/version/0-6-5/src/lib/resources/stbl/serialization/read-stbl.ts) in `stbl.h`
- [FNV hashing methods](https://github.com/sims4toolkit/hashing/blob/version/0-2-1/src/hashing.ts) in `hashing.h`

## Compiling & Running

I've been compiling & running this project using Clang on a 64-bit macOS system. There is no guarantee it will work with other compilers or on other machines.

```sh
# in root of c directory
clang ./src/main.c -o ./out/program
./out/program stbl $FILEPATH
```

## Known Issues

1. Currently, using the hashing and STBL parser functions in the same program can lead to a segfault. This segfault can be "fixed" by adding in `printf()` statements in the `load_stbl()` function, which indicates that some pointer(s) is/are being misused somewhere.
