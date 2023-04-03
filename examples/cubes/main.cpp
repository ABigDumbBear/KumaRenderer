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
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 0, 0);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 1, 0);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(0, 1, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.AddVertex(vertex);

  aMesh.AddIndex(0);
  aMesh.AddIndex(1);
  aMesh.AddIndex(3);
  aMesh.AddIndex(1);
  aMesh.AddIndex(2);
  aMesh.AddIndex(3);

  // Top face
  vertex.mPosition = Kuma3D::Vec3(0, 1, 0);
  vertex.mNormal = Kuma3D::Vec3(0, 1, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 1, 0);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 1, 1);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(0, 1, 1);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.AddVertex(vertex);

  aMesh.AddIndex(4);
  aMesh.AddIndex(5);
  aMesh.AddIndex(7);
  aMesh.AddIndex(5);
  aMesh.AddIndex(6);
  aMesh.AddIndex(7);

  // Back face
  vertex.mPosition = Kuma3D::Vec3(0, 0, 1);
  vertex.mNormal = Kuma3D::Vec3(0, 0, 1);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 0, 1);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 1, 1);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(0, 1, 1);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.AddVertex(vertex);

  aMesh.AddIndex(8);
  aMesh.AddIndex(9);
  aMesh.AddIndex(11);
  aMesh.AddIndex(9);
  aMesh.AddIndex(10);
  aMesh.AddIndex(11);

  // Left face
  vertex.mPosition = Kuma3D::Vec3(0, 0, 1);
  vertex.mNormal = Kuma3D::Vec3(-1, 0, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(0, 0, 0);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(0, 1, 0);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(0, 1, 1);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.AddVertex(vertex);

  aMesh.AddIndex(12);
  aMesh.AddIndex(13);
  aMesh.AddIndex(15);
  aMesh.AddIndex(13);
  aMesh.AddIndex(14);
  aMesh.AddIndex(15);

  // Bottom face
  vertex.mPosition = Kuma3D::Vec3(0, 0, 1);
  vertex.mNormal = Kuma3D::Vec3(0, -1, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 0, 1);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 0, 0);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(0, 0, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.AddVertex(vertex);

  aMesh.AddIndex(16);
  aMesh.AddIndex(17);
  aMesh.AddIndex(19);
  aMesh.AddIndex(17);
  aMesh.AddIndex(18);
  aMesh.AddIndex(19);

  // Right face
  vertex.mPosition = Kuma3D::Vec3(1, 0, 0);
  vertex.mNormal = Kuma3D::Vec3(1, 0, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 0;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 0, 1);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 0;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 1, 1);
  vertex.mTexCoords[0] = 1;
  vertex.mTexCoords[1] = 1;
  aMesh.AddVertex(vertex);
  vertex.mPosition = Kuma3D::Vec3(1, 1, 0);
  vertex.mTexCoords[0] = 0;
  vertex.mTexCoords[1] = 1;
  aMesh.AddVertex(vertex);

  aMesh.AddIndex(20);
  aMesh.AddIndex(21);
  aMesh.AddIndex(23);
  aMesh.AddIndex(21);
  aMesh.AddIndex(22);
  aMesh.AddIndex(23);
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
  //cubeTransform.Rotate(Kuma3D::Vec3(0, 1, 0), 45);
  std::vector<Kuma3D::Mat4> matrices;
  matrices.emplace_back(cubeTransform.GetMatrix());

  Kuma3D::Camera camera;
  camera.mViewportX = 1000;
  camera.mViewportY = 1000;

  // Run until instructed to close.
  while(!glfwWindowShouldClose(window))
  {
    glfwSwapBuffers(window);

    shader.Activate();
    shader.SetMat4("viewMatrix", Kuma3D::View(Kuma3D::Vec3(0, 0, 1),
                                              Kuma3D::Vec3(1, 0, 0),
                                              Kuma3D::Vec3(0, 0, 0)));
    shader.SetMat4("projectionMatrix", Kuma3D::Perspective(camera));
    mesh.DrawInstanced(shader, 1, matrices);

    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
