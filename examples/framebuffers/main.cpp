#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <random>

#include <KumaGL/Framebuffer.hpp>
#include <KumaGL/Mesh.hpp>
#include <KumaGL/Renderbuffer.hpp>
#include <KumaGL/Shader.hpp>
#include <KumaGL/Texture.hpp>
#include <KumaGL/Transform.hpp>

/******************************************************************************/
void FramebufferSizeCallback(GLFWwindow *aWindow, int aWidth, int aHeight) {
  glViewport(0, 0, aWidth, aHeight);
}

/******************************************************************************/
GLFWwindow *CreateWindow() {
  GLFWwindow *window = nullptr;

  // Initialize GLFW.
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW!" << std::endl;
    return window;
  }

  // Set the desired OpenGL version to 3.3.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // Use the core profile only; this removes backwards-compatible features
  // that are no longer needed for the engine.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Enable forward compatibility; this removes all deprecated features
  // in the desired version of OpenGL (3.3).
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

  // Enable double buffering.
  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

  // Create a new window.
  window = glfwCreateWindow(1280, 720, "cubes", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create window!" << std::endl;
    return window;
  }

  // Make the context current.
  glfwMakeContextCurrent(window);

  // Set any GLFW callbacks.
  glfwSetFramebufferSizeCallback(window, &FramebufferSizeCallback);

  return window;
}

/******************************************************************************/
bool InitializeContext(GLFWwindow &aWindow) {
  bool success = false;

  // Initialize GLAD.
  success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  if (!success) {
    std::cout << "Failed to initialize GLAD!" << std::endl;
    return success;
  }

  // Set up preliminary OpenGL state.
  glViewport(0, 0, 1280, 720);
  glEnable(GL_DEPTH_TEST);

  return true;
}

/******************************************************************************/
KumaGL::Transform CreateRandomTransform(std::random_device &aDevice) {
  KumaGL::Transform transform;

  std::mt19937 generator(aDevice());
  std::uniform_real_distribution<> dist(-25, 25);

  transform.Translate(
      KumaGL::Vec3(dist(generator), dist(generator), dist(generator) - 50));

  return transform;
}

/******************************************************************************/
int main() {
  auto window = CreateWindow();
  if (window == nullptr) {
    return -1;
  }

  auto success = InitializeContext(*window);
  if (!success) {
    return -1;
  }

  // Load textures.
  KumaGL::Texture cubeTexture;
  KumaGL::Texture screenTexture;

  cubeTexture.LoadFromFile("resources/texture.png");
  screenTexture.LoadFromData(nullptr, 1280, 720);

  glBindTexture(GL_TEXTURE_2D, cubeTexture.GetID());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Load shaders.
  KumaGL::Shader cubeShader;
  KumaGL::Shader screenShader;

  cubeShader.LoadFromFiles("resources/shaders/CubeShader.vert",
                           "resources/shaders/CubeShader.frag");
  screenShader.LoadFromFiles("resources/shaders/ScreenShader.vert",
                             "resources/shaders/ScreenShader.frag");

  // Create meshes.
  KumaGL::Mesh cubeMesh;
  KumaGL::Mesh screenMesh;

  cubeMesh.InitCube();
  screenMesh.InitQuad();

  // Create a framebuffer and a renderbuffer.
  KumaGL::Framebuffer fb;
  KumaGL::Renderbuffer rb;
  rb.SetStorageParameters(GL_DEPTH24_STENCIL8, 1280, 720);
  fb.AttachTexture(screenTexture);
  fb.AttachRenderbuffer(rb);

  // Generate a number of random transforms.
  std::random_device rd;
  std::vector<KumaGL::Transform> transforms;
  size_t numCubes = 10000;
  for (size_t i = 0; i < numCubes; ++i) {
    transforms.emplace_back(CreateRandomTransform(rd));
  }

  // Set the shader uniforms.
  cubeShader.Use();
  cubeShader.SetMat4("viewMatrix",
                     KumaGL::View(KumaGL::Vec3(0, 0, 1), KumaGL::Vec3(1, 0, 0),
                                  KumaGL::Vec3(0, 0, 0)));
  cubeShader.SetMat4("projectionMatrix",
                     KumaGL::Perspective(45, 1280, 720, 0.1, 100));

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  // Run until instructed to close.
  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);

    // Rotate each transform.
    for (auto &transform : transforms) {
      transform.Rotate(1, 1, 0);
    }

    // Add each transformation matrix to a vector.
    std::vector<KumaGL::Mat4> matrices;
    for (const auto &transform : transforms) {
      matrices.emplace_back(transform.GetMatrix());
    }

    // Copy the matrices into the cube instance buffer.
    glBindBuffer(GL_ARRAY_BUFFER, cubeMesh.GetInstanceBufferID());
    glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(KumaGL::Mat4),
                 matrices.data(), GL_DYNAMIC_DRAW);

    // Render to the framebuffer.
    fb.Bind();
    cubeShader.Use();
    glBindTexture(GL_TEXTURE_2D, cubeTexture.GetID());
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cubeMesh.DrawInstanced(numCubes);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Render the screen texture.
    screenShader.Use();
    glBindTexture(GL_TEXTURE_2D, screenTexture.GetID());
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    screenMesh.DrawInstanced(1);

    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
