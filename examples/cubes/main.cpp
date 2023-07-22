#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <numeric>
#include <random>

#include <KumaGL/Mesh.hpp>
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
  window = glfwCreateWindow(1280, 720, "framebuffers", nullptr, nullptr);
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
bool InitializeGL() {
  bool success = false;

  // Initialize GLAD.
  success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  if (!success) {
    std::cout << "Failed to initialize GLAD!" << std::endl;
    return success;
  }

  // Set up global OpenGL state.
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

  auto success = InitializeGL();
  if (!success) {
    return -1;
  }

  // Load the shader.
  KumaGL::Shader shader;
  shader.LoadFromFiles("resources/shaders/CubeShader.vert",
                       "resources/shaders/CubeShader.frag");

  // Load the texture.
  KumaGL::Texture texture;
  texture.LoadFromFile("resources/texture.png");

  // Set texture filtering options to linear; we don't want it to be blurry.
  texture.SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  texture.SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  texture.GenerateMipmap();

  // Create a cube mesh.
  KumaGL::Mesh mesh;
  mesh.InitCube();

  // Generate a number of random transforms.
  std::random_device rd;
  std::vector<KumaGL::Transform> transforms;
  for (int i = 0; i < 10000; ++i) {
    transforms.emplace_back(CreateRandomTransform(rd));
  }

  // Set the shader uniforms.
  shader.SetMat4("viewMatrix",
                 KumaGL::View(KumaGL::Vec3(0, 0, 1), KumaGL::Vec3(1, 0, 0),
                              KumaGL::Vec3(0, 0, 0)));
  shader.SetMat4("projectionMatrix",
                 KumaGL::Perspective(45, 1280, 720, 0.1, 100));

  // Run until instructed to close.
  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    mesh.mInstanceBuffer.CopyData(GL_ARRAY_BUFFER,
                                  matrices.size() * sizeof(KumaGL::Mat4),
                                  matrices.data(), GL_DYNAMIC_DRAW);

    // Draw the cube a number of times.
    shader.Bind();
    texture.Bind();
    mesh.DrawInstanced(10000);

    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
