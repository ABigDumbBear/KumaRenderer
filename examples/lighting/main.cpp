#include "Mesh.hpp"
#include "Transform.hpp"
#include "Vec3.hpp"
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>

#include <Shader.hpp>
#include <Texture.hpp>

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
  auto window = glfwCreateWindow(1280, 720, "cubes", nullptr, nullptr);
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

  glViewport(0, 0, 1280, 720);
  glEnable(GL_DEPTH_TEST);

  // Load the shader.
  KumaGL::Shader shader;
  shader.LoadFromFiles("resources/shaders/Shader.vert",
                       "resources/shaders/Shader.frag");

  // Load the textures.
  KumaGL::Texture diffuse;
  KumaGL::Texture specular;
  diffuse.LoadFromFile("resources/textures/diffuse.png");
  specular.LoadFromFile("resources/textures/specular.png");

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, diffuse.GetID());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glGenerateMipmap(GL_TEXTURE_2D);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, specular.GetID());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Set the shader uniforms.
  shader.Use();
  shader.SetMat4("viewMatrix",
                 KumaGL::View(KumaGL::Vec3(0, 0, 1), KumaGL::Vec3(1, 0, 0),
                              KumaGL::Vec3(0, 0, 0)));
  shader.SetMat4("projectionMatrix",
                 KumaGL::Perspective(45, 1280, 720, 0.1, 100));

  shader.SetInt("diffuse", 0);
  shader.SetInt("specular", 1);
  shader.SetFloat("shininess", 128);

  shader.SetVec3("lightColor", KumaGL::Vec3(1, 0.5, 0));

  shader.SetVec3("viewPos", KumaGL::Vec3(0, 0, 0));

  // Create a cube mesh.
  KumaGL::Mesh cube;
  cube.InitCube();

  // Create a transform for the cube object and for the light.
  KumaGL::Transform obj;
  KumaGL::Transform light;

  obj.SetPosition(KumaGL::Vec3(0, 0, -5));
  light.SetPosition(KumaGL::Vec3(0, -15, 10));

  // Run until instructed to close.
  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Translate the light.
    light.Translate(KumaGL::Vec3(0, 0.1, 0));

    // Set the light position in the shader.
    shader.SetVec3("lightPos", light.GetWorldPosition());

    // Rotate the cube object.
    obj.Rotate(0, 1, 0);

    // Copy the cube object's matrix to the instance buffer.
    glBindBuffer(GL_ARRAY_BUFFER, cube.GetInstanceBufferID());
    glBufferData(GL_ARRAY_BUFFER, sizeof(KumaGL::Mat4),
                 (void *)(&obj.GetMatrix()), GL_DYNAMIC_DRAW);

    // Draw the cube.
    cube.DrawInstanced(shader, 1);

    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
