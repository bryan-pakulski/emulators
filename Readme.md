# About
Collection of emulator projects written in C++ these are self-learning projects and don't attempt to compete with more complete releases

Feel free to dig apart any source code and re-use in any other projects

# Required tools for compiling/testing projects:

g++ (C++11 standard)
valgrind
patchelf

# Required libraries

These projects have been set up to "minimalize" the need for installing external libraries globally (all required library .so files can be placed in the respective "lib" folder)
On compilation these .so libraries will be copied over to the bin folder and linked using patchelf so the release is "portable" just make sure to copy the "lib" folder as well

Note that you can also use a static library without any issue, no need to copy the "lib" folder in that situation