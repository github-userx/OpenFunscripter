# OpenFunscripter
I swear this is a C++ project despite what the statistic on this repo says 😅

The project is based on OpenGL, SDL2, ImGui, & libmpv ( and I'm kind of proud of it ).

![OpenFunscripter Screenshot](https://github.com/gagax1234/OpenFunscripter/raw/master/OpenFunscripter.jpg)

### How to build ( for people who want to contribute or fork )
1. clone the repository
2. run `git submodule update --init --recursive`
3. Run cmake and compile ( on windows just use visual studio 2019 with cmake support )
4. Copy the data directory next to the executable.
5. - On Windows make sure to copy the mpv-1.dll into the same directory as the executable. 
   - On Linux you'll need pkg-config & libmpv installed


### Windows libmpv binaries used
Currently using: [mpv-dev-x86_64-20200816-git-7f67c52.7z (it's part of the repository)](https://sourceforge.net/projects/mpv-player-windows/files/libmpv/)


### Platforms
I have built this successfully for Linux & Windows in theory OSX should work as well but I can't test that.  
I will probably only provide binaries for Windows.
