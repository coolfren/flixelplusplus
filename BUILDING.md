# PC
## Linux
You will need the following dependencies:
- SDL2
- SDL2_image
- SDL2_ttf
- OpenAL
- libvorbis
- gcc
- make
- cmake

1. Run ``make pc``   
    1.1. Run ``make pc PLATFORM=1`` for compiling with SDL 1.2  
    1.2. Run ``make pc PLATFORM=2`` for compiling with SDL 2  
    1.3. Run ``make pc PLATFORM=3`` for compiling with SDL 2 and OpenGL

2. Run ``make install`` (with root permissions)

After installing, libflixel++.so will be placed in /usr/lib/ and the neccessary headers will be placed in /usr/include/flixel++

To change the framework(s):
1. Run ``make uninstall`` (if did make install)
2. Run ``make clean``
3. Follow the instructions above

## Windows
Should theoretically support Windows?

# Consoles
## Nintendo Switch (WIP)
