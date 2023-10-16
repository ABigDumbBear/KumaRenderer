# KumaGL
KumaGL is a small 3D rendering library for OpenGL.

The goals of KumaGL are:
* to make managing OpenGL state more automatic
* to provide a basis for common rendering scenarios

Unlike some larger and more ambitious graphics libraries, KumaGL does not intend to wrap every last bit of OpenGL functionality. Rather, it provides a handful of utility classes to help any rendering-focused projects get off the ground.

## Features
* Automatic creation and deletion of OpenGL objects
* Convenient 3D math classes
* Simple instanced rendering
* GLSL shader support
* Texture loading/mapping
* Framebuffers and renderbuffers

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
cmake .. -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF
make install
```
