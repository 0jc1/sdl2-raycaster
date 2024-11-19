# SDL2 Raycaster
A basic SDL2 raycasting engine written in C++. Raycasting is a rendering technique to create a puedo 3D game from a 2D map. This was done by casting rays for each horizontal screen pixel and calculating the length of the rays using DDA algorithm.

## Screenshot
![eyJhbGciOiJIUzI1NiJ9 eyJpbWciOiJfMWFhNjhiZDAyZDdjYTMwZjI4ZTdmZDcyYmIyMjYzNjIifQ hIVZ5ViT5pkWYZiyExs9b1qyG2560jVeXvxE3MPVkuc-png](https://github.com/jcook0/sdl2-raycaster/assets/52017130/95ad71e5-ce50-4607-823e-858a04a17847)

## Setup 

### Linux: 
First, make sure you have a C++ compiler installed. Then, install SDL2 and CMake:
```
sudo apt-get install libsdl2-dev cmake make g++
```

Build and compile:
```
cmake 
make
```

### Windows: 
Download and install VS with C++ or MinGW-w64. You also will need to download SDL2 for Windows. Then, change the path in CMakeLists.txt to your /SDL2/ folder. 
Make sure `SDL2.dll` is in the right directory.

Build and compile:
```
cmake .. -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release
```
Replace "Visual Studio 16 2019" with your version of Visual Studio. 

## References
https://lodev.org/cgtutor/raycasting.html

https://lazyfoo.net/tutorials/SDL/
