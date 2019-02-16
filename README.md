
OpenGL CMake Skeleton WebAssembly[![Build Status](https://travis-ci.org/ArthurSonzogni/OpenGL_CMake_Skeleton_WebAssembly.svg?branch=master)](https://travis-ci.org/ArthurSonzogni/OpenGL_CMake_Skeleton_WebAssembly)
=======================

A ready to use C++11 CMake skeleton using **GLFW**, **Glew** and **glm**. (use git submodules)

It can compile for the Web with WebAssembly thanks to emscripten, as well as on
Linux, Windows and Mac.

Shader class and example Application are included.

![output result](output.gif)

I am open to any comments and contributions.

git submodules :
================

This project use the git submodules system.
To clone this repository you must add the --recursive option.
```
git clone --recursive git@github.com:ArthurSonzogni/OpenGL_CMake_Skeleton_WebAssembly.git
```
Alternatively, if you don't used the --recursive option, you can type:
* git submodule init
* git submodule update

Requirement:
============
* C++11 compiler
* cmake (>= 3.0)
* OpenGL version (>=3.0)
* Some standard library depending on your platform

usage (WebAssembly) : 
---------------------
Install emscripten, then
```bash
mkdir build_emscripten
cd build_emscripten
CC=emcc CXX=em++ cmake ..
make
python -m SimpleHTTPServer 8000
```

Now, visit [http://localhost:8000](http://localhost:8000)

usage (Linux) : 
---------------
Some standard library to install:
```bash
sudo apt-get install cmake libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev

Open the directory into a terminal
```bash
mkdir build
cd build
cmake ..
./main
```

usage (Windows) :
-----------------
For instance :
* cmake-gui .
* Configure (Choose for example Visual Studio generator)
* Generate
Launch the generated project in your favorite IDE and run it.
