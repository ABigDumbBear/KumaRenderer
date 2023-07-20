#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>

#include <KumaGL/Font.hpp>
#include <KumaGL/Shader.hpp>
#include <KumaGL/Texture.hpp>
#include <KumaGL/Transform.hpp>

/******************************************************************************/
void FramebufferSizeCallback(GLFWwindow *aWindow, int aWidth, int aHeight) {
  glViewport(0, 0, aWidth, aHeight);
}

/******************************************************************************/
int main() {
  // Initialize GLFW.
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW!" << std::endl;
    return -1;
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
  auto window = glfwCreateWindow(1280, 720, "text", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create window!" << std::endl;
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLAD.
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD!" << std::endl;
    return -1;
  }

  // Set any GLFW callbacks.
  glfwSetFramebufferSizeCallback(window, &FramebufferSizeCallback);

  // Set up preliminary OpenGL state.
  glViewport(0, 0, 1280, 720);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Load the shader.
  KumaGL::Shader shader;
  shader.LoadFromFiles("resources/shaders/Text.vert",
                       "resources/shaders/Text.frag");

  // Load the font.
  KumaGL::Font font;
  font.LoadFromFile("resources/font/Roboto-Regular.ttf");

  // Create a mesh and update its geometry to display some text.
  KumaGL::Mesh mesh;
  font.UpdateMeshToDisplayText(mesh, "This is some text.");

  KumaGL::Transform meshTransform;
  meshTransform.SetPosition(KumaGL::Vec3(5, 69, 0));

  // Set the shader uniforms.
  shader.SetMat4("modelMatrix", meshTransform.GetMatrix());
  shader.SetMat4("projectionMatrix", KumaGL::Orthographic(1280, 720, 0, 100));

  // Run until instructed to close.
  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.Bind();
    mesh.Draw();

    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
