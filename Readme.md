# About
Collection of emulator projects written in C++ - These are self-learning projects and don't attempt to compete with more complete releases so for most these will only be entertaining from an academic point of view``

Feel free to dig apart any source code and re-use in any other projects, just make sure to keep in line with the attached LICENSE file.

## CoreLink
This is the front end of the application, attempts to be similar to retro-arch, allowing a user to load core files (dynamically built libraries) and run different emulator projects from a single ui

### Building
A linux build script is available under `scripts/build`. It will build the main application as well as dynamic libraries for the cores, a packaged release is saved under the root directory: `CoreLink.tar.gz`

### Cores
Currently supported cores:
- chip8