#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <Mesh.hpp>
#include <Shader.hpp>
#include <Texture.hpp>

#include <Transform.hpp>

#include <MathUtil.hpp>

/******************************************************************************/
void CreateCubeMesh(Kuma3D::Mesh& aMesh)
{
  Kuma3D::MeshVertex vertex;

  // Front face
  vertex.mPosition = Kuma3D::Vec3(0, 0, 0);
  vertex.mNormal = Kuma3D::Vec3(0, 0, -1);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 0, 0);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 1, 0);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(0, 1, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);

  aMesh.mIndices.emplace_back(0);
  aMesh.mIndices.emplace_back(1);
  aMesh.mIndices.emplace_back(3);
  aMesh.mIndices.emplace_back(1);
  aMesh.mIndices.emplace_back(2);
  aMesh.mIndices.emplace_back(3);

  // Top face
  vertex.mPosition = Kuma3D::Vec3(0, 1, 0);
  vertex.mNormal = Kuma3D::Vec3(0, 1, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 1, 0);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 1, 1);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(0, 1, 1);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);

  aMesh.mIndices.emplace_back(4);
  aMesh.mIndices.emplace_back(5);
  aMesh.mIndices.emplace_back(7);
  aMesh.mIndices.emplace_back(5);
  aMesh.mIndices.emplace_back(6);
  aMesh.mIndices.emplace_back(7);

  // Back face
  vertex.mPosition = Kuma3D::Vec3(0, 0, 1);
  vertex.mNormal = Kuma3D::Vec3(0, 0, 1);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 0, 1);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 1, 1);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(0, 1, 1);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);

  aMesh.mIndices.emplace_back(8);
  aMesh.mIndices.emplace_back(9);
  aMesh.mIndices.emplace_back(11);
  aMesh.mIndices.emplace_back(9);
  aMesh.mIndices.emplace_back(10);
  aMesh.mIndices.emplace_back(11);

  // Left face
  vertex.mPosition = Kuma3D::Vec3(0, 0, 1);
  vertex.mNormal = Kuma3D::Vec3(-1, 0, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(0, 0, 0);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(0, 1, 0);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(0, 1, 1);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);

  aMesh.mIndices.emplace_back(12);
  aMesh.mIndices.emplace_back(13);
  aMesh.mIndices.emplace_back(15);
  aMesh.mIndices.emplace_back(13);
  aMesh.mIndices.emplace_back(14);
  aMesh.mIndices.emplace_back(15);

  // Bottom face
  vertex.mPosition = Kuma3D::Vec3(0, 0, 1);
  vertex.mNormal = Kuma3D::Vec3(0, -1, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 0, 1);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 0, 0);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(0, 0, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);

  aMesh.mIndices.emplace_back(16);
  aMesh.mIndices.emplace_back(17);
  aMesh.mIndices.emplace_back(19);
  aMesh.mIndices.emplace_back(17);
  aMesh.mIndices.emplace_back(18);
  aMesh.mIndices.emplace_back(19);

  // Right face
  vertex.mPosition = Kuma3D::Vec3(1, 0, 0);
  vertex.mNormal = Kuma3D::Vec3(1, 0, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 0, 1);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 1, 1);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.mVertices.emplace_back(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 1, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
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

  // Load the texture.
  Kuma3D::Texture texture;
  texture.LoadFromFile("resources/texture.png");

  // Create a cube.
  Kuma3D::Mesh mesh;
  CreateCubeMesh(mesh);
  Kuma3D::Transform cubeTransform;
  cubeTransform.SetPosition(Kuma3D::Vec3(0, 0, -10));

  // Set the shader uniforms.
  shader.Activate();
  shader.SetMat4("viewMatrix", Kuma3D::View(Kuma3D::Vec3(0, 0, 1),
                                            Kuma3D::Vec3(1, 0, 0),
                                            Kuma3D::Vec3(0, 0, 0)));
  shader.SetMat4("projectionMatrix", Kuma3D::Perspective(45, 1000, 1000, 0.1, 100));

  std::vector<Kuma3D::Mat4> matrices;

  // Run until instructed to close.
  while(!glfwWindowShouldClose(window))
  {
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cubeTransform.Rotate(Kuma3D::Vec3(0, 1, 0), 1);
    matrices.clear();
    matrices.emplace_back(cubeTransform.GetMatrix());

    // Copy data into the cube instance buffer.
    glBindBuffer(GL_ARRAY_BUFFER, mesh.GetInstanceBufferID());
    glBufferData(GL_ARRAY_BUFFER,
                 matrices.size() * sizeof(Kuma3D::Mat4),
                 &matrices[0],
                 GL_DYNAMIC_DRAW);
    mesh.DrawInstanced(shader, 1);

    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
