#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <Font.hpp>
#include <Shader.hpp>

/******************************************************************************/
int main()
{
  // Initialize GLFW.
  if(!glfwInit())
  {
    std::cout << "Failed to initialize GLFW!" << std::endl;
    return -1;
  }

  // Set the desired OpenGL version to 3.3.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // Use the core profile only; this removes backwards-compatible features
  // that are no longer needed for the engine.
  glfwWindowHint(GLFW_OPENGL_PROFILE,
                 GLFW_OPENGL_CORE_PROFILE);

  // Enable forward compatibility; this removes all deprecated features
  // in the desired version of OpenGL (3.3).
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                 GLFW_TRUE);

  // Enable double buffering.
  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

  // Create a new window.
  auto window = glfwCreateWindow(1000, 1000, "cubes", nullptr, nullptr);
  if(window == nullptr)
  {
    std::cout << "Failed to create window!" << std::endl;
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLAD.
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD!" << std::endl;
    return -1;
  }

  glViewport(0, 0, 1000, 1000);
  glEnable(GL_DEPTH_TEST);

  // Load the shader.
  Kuma3D::Shader shader;
  shader.LoadFromFiles("resources/shaders/CubeShader.vert",
                       "resources/shaders/CubeShader.frag");

  // Load the font.
  Kuma3D::Font font;
  font.LoadFromFile("resources/fonts/Roboto-Regular.ttf");

  glfwTerminate();
  return 0;
}
