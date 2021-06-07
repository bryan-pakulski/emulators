# About
Collection of emulator projects written in C++ - These are self-learning projects and don't attempt to compete with more complete releases so for most these will only be entertaining from an academic point of view :)

Feel free to dig apart any source code and re-use in any other projects, just make sure to keep in line with the attached LICENSE file.

# Required tools for compiling/testing projects:

- g++ (C++11 standard)
- valgrind
- patchelf

# Required libraries

### Portable Setup

These projects have been set up to "minimalize" the need for installing external libraries globally via package manager (all required library .so / .a files can be placed in the respective "lib" folder per project).

On compilation any dynamic libraries will be copied over to the bin release folder and linked using patchelf so the executable is "portable" just make sure to copy the "lib" folder as well.

Note: that you can also use a static library without any issues, no need to copy the "lib" folder in that situation.

### Normal Setup

install libraries via your package manager as normal.