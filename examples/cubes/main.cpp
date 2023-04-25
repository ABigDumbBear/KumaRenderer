#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <random>

#include <Mesh.hpp>
#include <Shader.hpp>
#include <Texture.hpp>

#include <Transform.hpp>

#include <MathUtil.hpp>

/******************************************************************************/
void CreateCubeMesh(KumaGL::Mesh& aMesh)
{
  KumaGL::MeshVertex vertex;

  // Front face
  vertex.mPosition = KumaGL::Vec3(-0.5, -0.5, 0.5);
  vertex.mNormal = KumaGL::Vec3(0, 0, -1);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(0.5, -0.5, 0.5);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(0.5, 0.5, 0.5);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(-0.5, 0.5, 0.5);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);

  aMesh.mIndices.emplace_back(0);
  aMesh.mIndices.emplace_back(1);
  aMesh.mIndices.emplace_back(3);
  aMesh.mIndices.emplace_back(1);
  aMesh.mIndices.emplace_back(2);
  aMesh.mIndices.emplace_back(3);

  // Top face
  vertex.mPosition = KumaGL::Vec3(-0.5, 0.5, 0.5);
  vertex.mNormal = KumaGL::Vec3(0, 1, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(0.5, 0.5, 0.5);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(0.5, 0.5, -0.5);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(-0.5, 0.5, -0.5);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);

  aMesh.mIndices.emplace_back(4);
  aMesh.mIndices.emplace_back(5);
  aMesh.mIndices.emplace_back(7);
  aMesh.mIndices.emplace_back(5);
  aMesh.mIndices.emplace_back(6);
  aMesh.mIndices.emplace_back(7);

  // Back face
  vertex.mPosition = KumaGL::Vec3(-0.5, -0.5, -0.5);
  vertex.mNormal = KumaGL::Vec3(0, 0, 1);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(0.5, -0.5, -0.5);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(0.5, 0.5, -0.5);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(-0.5, 0.5, -0.5);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);

  aMesh.mIndices.emplace_back(8);
  aMesh.mIndices.emplace_back(9);
  aMesh.mIndices.emplace_back(11);
  aMesh.mIndices.emplace_back(9);
  aMesh.mIndices.emplace_back(10);
  aMesh.mIndices.emplace_back(11);

  // Left face
  vertex.mPosition = KumaGL::Vec3(-0.5, -0.5, -0.5);
  vertex.mNormal = KumaGL::Vec3(-1, 0, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(-0.5, -0.5, 0.5);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(-0.5, 0.5, 0.5);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(-0.5, 0.5, -0.5);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);

  aMesh.mIndices.emplace_back(12);
  aMesh.mIndices.emplace_back(13);
  aMesh.mIndices.emplace_back(15);
  aMesh.mIndices.emplace_back(13);
  aMesh.mIndices.emplace_back(14);
  aMesh.mIndices.emplace_back(15);

  // Bottom face
  vertex.mPosition = KumaGL::Vec3(-0.5, -0.5, -0.5);
  vertex.mNormal = KumaGL::Vec3(0, -1, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(0.5, -0.5, -0.5);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(0.5, -0.5, 0.5);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(-0.5, -0.5, 0.5);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);

  aMesh.mIndices.emplace_back(16);
  aMesh.mIndices.emplace_back(17);
  aMesh.mIndices.emplace_back(19);
  aMesh.mIndices.emplace_back(17);
  aMesh.mIndices.emplace_back(18);
  aMesh.mIndices.emplace_back(19);

  // Right face
  vertex.mPosition = KumaGL::Vec3(0.5, -0.5, 0.5);
  vertex.mNormal = KumaGL::Vec3(1, 0, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(0.5, -0.5, -0.5);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(0.5, 0.5, -0.5);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = KumaGL::Vec3(0.5, 0.5, 0.5);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);

  aMesh.mIndices.emplace_back(20);
  aMesh.mIndices.emplace_back(21);
  aMesh.mIndices.emplace_back(23);
  aMesh.mIndices.emplace_back(21);
  aMesh.mIndices.emplace_back(22);
  aMesh.mIndices.emplace_back(23);

  aMesh.UpdateVertices();
  aMesh.UpdateIndices();
}

/******************************************************************************/
KumaGL::Transform CreateRandomTransform(std::random_device& aDevice)
{
  KumaGL::Transform transform;

  std::mt19937 generator(aDevice());
  std::uniform_real_distribution<> dist(-25, 25);

  transform.Translate(KumaGL::Vec3(dist(generator), dist(generator), dist(generator) - 50));

  return transform;
}

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
  auto window = glfwCreateWindow(1280, 720, "cubes", nullptr, nullptr);
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

  glViewport(0, 0, 1280, 720);
  glEnable(GL_DEPTH_TEST);

  // Load the shader.
  KumaGL::Shader shader;
  shader.LoadFromFiles("resources/shaders/CubeShader.vert",
                       "resources/shaders/CubeShader.frag");

  // Load the texture.
  KumaGL::Texture texture;
  glBindTexture(GL_TEXTURE_2D, texture.GetID());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  texture.LoadFromFile("resources/texture.png");

  // Create a cube mesh.
  KumaGL::Mesh mesh;
  CreateCubeMesh(mesh);

  // Generate a number of random transforms.
  std::random_device rd;
  std::vector<KumaGL::Transform> transforms;
  for(int i = 0; i < 10000; ++i)
  {
    transforms.emplace_back(CreateRandomTransform(rd));
  }

  // Set the shader uniforms.
  shader.Use();
  shader.SetMat4("viewMatrix", KumaGL::View(KumaGL::Vec3(0, 0, 1),
                                            KumaGL::Vec3(1, 0, 0),
                                            KumaGL::Vec3(0, 0, 0)));
  shader.SetMat4("projectionMatrix", KumaGL::Perspective(45, 1280, 720, 0.1, 100));

  // Run until instructed to close.
  while(!glfwWindowShouldClose(window))
  {
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rotate each transform.
    for(auto& transform : transforms)
    {
      transform.SetRotation(0, sin(glfwGetTime()) * 180, 0);
    }

    // Add each transformation matrix to a vector.
    std::vector<KumaGL::Mat4> matrices;
    for(const auto& transform : transforms)
    {
      matrices.emplace_back(transform.GetMatrix());
    }

    // Copy the matrices into the cube instance buffer.
    glBindBuffer(GL_ARRAY_BUFFER, mesh.GetInstanceBufferID());
    glBufferData(GL_ARRAY_BUFFER,
                 matrices.size() * sizeof(KumaGL::Mat4),
                 matrices.data(),
                 GL_DYNAMIC_DRAW);

    // Draw the cube a number of times.
    mesh.DrawInstanced(shader, 10000);

    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
