# KumaGL
KumaGL is a small 3D rendering library for OpenGL.

The goals of KumaGL are:
* to make managing OpenGL state more automatic
* to provide a basis for common rendering scenarios
* to incorporate some 3rd-party libraries for loading and storing resources (like textures and models)

Unlike some larger and more ambitious graphics libraries, KumaGL does not intend to wrap every last bit of OpenGL functionality. Rather, it provides a handful of utility classes to help any rendering-focused projects get off the ground.

## Features
* Simple 3D math implementation
* Automatic creation and deletion of vertex buffers
* Simple instanced rendering
* GLSL shader loading
* Texture loading/mapping
* 3D model loading/rendering
* Font loading/rendering

## Planned Features
* Framebuffers and renderbuffers
* Skeletal animation

## External dependencies
KumaGL depends on a few other libraries:
* Assimp (for 3D model loading)
* Freetype (for font loading)

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
