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

1. Run ``make pc``
2. Run ``make install`` (with root permissions)

After installing, libflixel++.so will be placed in /usr/lib/ and the neccessary headers will be placed in /usr/include/flixel++

## Windows
### Visual Studio 2022 (Check the Windows branch)
You will need the following dependencies:
- SDL2
- SDL2_image
- SDL2_ttf
- OpenAL
- libvorbis
- gcc

To install OpenAL and libvorbis and add the libraries:
1. Install VCPKG by following the intructions on the website: ``https://vcpkg.io/en/getting-started.html``

2. Run ``vcpkg install openal-soft:x64-windows``

3. Run ``vcpkg install libvorbis:x64-windows``

4. Put the headers,lib and dlls into each folder respectively:
    - Headers: includes
    - Lib: lib
    - Dlls: lib/dlls 


# Consoles
## Nintendo Switch (WIP)
