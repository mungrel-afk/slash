# Slash

 Game about slashing, dodging, and parrying

## Building

Requires `g++` and GNU `make`. The Makefile detects the OS and links the matching
prebuilt raylib 6.0 library from `lib/windows/` or `lib/linux/`.

```sh
make build   # compile (Slash.exe on Windows, Slash on Linux)
make run     # compile and launch
make clean   # remove the executable
```

On Windows, use a 64-bit MinGW-w64 toolchain (e.g. MinGW-Builds, w64devkit, or MSYS2).
