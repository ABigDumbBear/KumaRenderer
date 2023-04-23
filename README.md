# KumaGL
KumaGL is a 3D rendering library for OpenGL that aims to be as flexible as possible. In order to achieve this, it prioritizes using raw OpenGL over any wrapper/boilerplate classes (except where it makes sense).

## Features
* Simple 3D math implementation (3D vectors, 4D matrices)
* Automatic buffer creation via the Mesh class
* Simple instanced rendering via the Mesh class
* 2D textures
* Font loading/rendering (requires Freetype)
* 3D model loading/rendering (requires Assimp)

## Planned Features
* More detailed materials (normal maps, bump maps, etc.)
* Phong lighting
* Custom framebuffers

## External dependencies
KumaGL can make use of some 3rd party libraries for additional features. These optional libraries are as follows:
* GLFW (for the example projects)
* Freetype (for font loading/rendering)
* Assimp (for 3D model loading/rendering)

## Building
To build KumaGL, the standard CMake procedure can be followed (note that it assumes all external dependencies are installed):
```
cd KumaGL
mkdir build
cd build
cmake ..
make install
```

Alternatively, KumaGL can be built without any external dependencies like so:
```
cd KumaGL
mkdir build
cd build
cmake -DTEXT_SUPPORT=OFF -DMODEL_SUPPORT=OFF -DBUILD_EXAMPLES=OFF ..
make install
```
