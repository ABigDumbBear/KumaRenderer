# KumaGL
KumaGL is a small 3D rendering library for OpenGL. The goal of KumaGL is not to be a monolithic, one-stop-shop for all use cases when it comes to rendering. Rather, it provides a few wrapper classes to make managing OpenGL a little easier and a little more automatic.

## Features
* Simple 3D math implementation
* Automatic creation and deletion of vertex buffers via the Mesh class
* Simple instanced rendering via the Mesh class
* GLSL shader loading
* Texture loading/mapping
* 3D model loading/rendering
* Font loading/rendering

## Planned Features
* Custom framebuffers

## External dependencies
KumaGL depends on a few other libraries:
* Freetype (for font loading)
* Assimp (for 3D model loading)

Additionally, to build the included example projects, you will need to install GLFW.

## Building
To build KumaGL along with the example projects and unit tests, the standard CMake procedure can be followed:
```
cd KumaGL
mkdir build
cd build
cmake ..
make install
```

Alternatively, if you just want to build the library:
```
cd KumaGL
mkdir build
cd build
cmake -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF ..
make install
```
