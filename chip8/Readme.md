# Compiling
- run make init to create missing folders (dependencies / lib)
- Add library files into lib
- Add below files into dependencies folder

# Required files
- chip8 roms (can be easily found on the internet)
- OpenSans-Regular.ttf

# Required libraries (linux)
- libsdl2-dev
- libsdl2-ttf
## Lib packages
You can install .so .a linking binaries directly without the use of a package manager by following these steps:

- Create lib folder in this directory
- Add required .so / .a binaries from above requirements

The make file will automatically accomodate these and link them to the binary

Note: You should download the external libraries only from a trusted external source i.e. Arch linux mirrors.