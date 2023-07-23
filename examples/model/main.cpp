#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>

#include <KumaGL/Model.hpp>
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
  shader.LoadFromFiles("resources/shaders/Model.vert",
                       "resources/shaders/Model.frag");

  // Load the model.
  KumaGL::Model model;
  model.LoadFromFile("resources/model/Spitfire.obj");

  // Load the textures.
  KumaGL::Texture tex;
  tex.LoadFromFile("resources/model/Spitfire_Red.png", GL_RGB);
  tex.SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  tex.SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  tex.GenerateMipmap();
  tex.Bind();
  glActiveTexture(GL_TEXTURE0);

  // Set shader uniforms.
  KumaGL::Transform modelTransform;
  modelTransform.SetPosition(KumaGL::Vec3(0, 0, -10));
  shader.SetMat4("modelMatrix", modelTransform.GetMatrix());
  shader.SetMat4("viewMatrix",
                 KumaGL::View(KumaGL::Vec3(0, 0, 1), KumaGL::Vec3(1, 0, 0),
                              KumaGL::Vec3(0, 0, 0)));
  shader.SetMat4("projectionMatrix",
                 KumaGL::Perspective(45, 1280, 720, 0.1, 100));
  shader.SetInt("texSampler", 0);

  // Run until instructed to close.
  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    modelTransform.Rotate(0, 1, 0);
    shader.SetMat4("modelMatrix", modelTransform.GetMatrix());

    shader.Bind();
    model.Draw();

    glfwPollEvents();
  }

  shader.Delete();
  model.Delete();
  tex.Delete();

  glfwTerminate();
  return 0;
}
