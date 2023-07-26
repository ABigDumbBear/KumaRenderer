#include <algorithm>
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <array>
#include <iostream>

#include <KumaGL/Framebuffer.hpp>
#include <KumaGL/Mesh.hpp>
#include <KumaGL/Renderbuffer.hpp>
#include <KumaGL/Shader.hpp>
#include <KumaGL/Texture.hpp>
#include <KumaGL/Transform.hpp>

/******************************************************************************/
int screenWidth = 1280;
int screenHeight = 720;

/******************************************************************************/
struct RenderInfo {
  KumaGL::Shader mCubeShader;
  KumaGL::Shader mDepthShader;

  KumaGL::Texture mCubeDiffuse;
  KumaGL::Texture mCubeSpecular;
  KumaGL::Texture mDepthMap;

  KumaGL::Mesh mCubeMesh;
  KumaGL::Mesh mQuadMesh;

  KumaGL::Framebuffer mShadowBuffer;

  void Setup() {
    // Configure the shaders.
    mCubeShader.LoadFromFiles("resources/shaders/Shader.vert",
                              "resources/shaders/Shader.frag");

    mCubeShader.SetMat4("viewMatrix", KumaGL::View(KumaGL::Vec3(0, 0, 1),
                                                   KumaGL::Vec3(1, 0, 0),
                                                   KumaGL::Vec3(0, 0, 0)));
    mCubeShader.SetMat4("projectionMatrix",
                        KumaGL::Perspective(45, 1280, 720, 0.1, 100));

    mCubeShader.SetInt("diffuseTexture", 1);
    mCubeShader.SetInt("specularTexture", 2);
    mCubeShader.SetFloat("shininess", 256);
    mCubeShader.SetVec3("lightColor", KumaGL::Vec3(1, 0.9, 0.7));
    mCubeShader.SetVec3("lightPos", KumaGL::Vec3(0, 0, 10));
    mCubeShader.SetVec3("viewPos", KumaGL::Vec3(0, 0, 0));

    // Configure the textures.
    mCubeDiffuse.LoadFromFile("resources/textures/diffuse.png");
    mCubeDiffuse.SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    mCubeDiffuse.SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    mCubeDiffuse.Bind(GL_TEXTURE1);

    mCubeSpecular.LoadFromFile("resources/textures/specular.png");
    mCubeSpecular.SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    mCubeSpecular.SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    mCubeSpecular.Bind(GL_TEXTURE2);

    mDepthMap.LoadFromData(nullptr, 1280, 720, GL_DEPTH_COMPONENT, GL_FLOAT);
    mDepthMap.SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    mDepthMap.SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configure the meshes.
    mCubeMesh.InitCube();
    mQuadMesh.InitQuad();

    // Configure the framebuffer.
    mShadowBuffer.AttachTexture(mDepthMap, GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                GL_TEXTURE_2D);
    mShadowBuffer.Bind();
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    mShadowBuffer.Unbind();
  }

  void Delete() {
    mCubeShader.Delete();
    mDepthShader.Delete();
    mCubeDiffuse.Delete();
    mCubeSpecular.Delete();
    mDepthMap.Delete();
    mCubeMesh.Delete();
    mQuadMesh.Delete();
    mShadowBuffer.Delete();
  }
};

/******************************************************************************/
struct Scene {
  KumaGL::Transform mPlaneTransform;
  KumaGL::Transform mLightTransform;
  std::array<KumaGL::Transform, 5> mCubeTransforms;

  void Setup() {
    mPlaneTransform.Rotate(45, 0, 0);
    mPlaneTransform.Scale(5, 5, 1);
    mPlaneTransform.Translate(KumaGL::Vec3(0, 0, -20));

    mLightTransform.SetPosition(KumaGL::Vec3(0, 0, 10));

    mCubeTransforms[0].SetPosition(KumaGL::Vec3(0, 0, -10));
    mCubeTransforms[1].SetPosition(KumaGL::Vec3(0, 2, -10));
    mCubeTransforms[2].SetPosition(KumaGL::Vec3(2, 0, -10));
    mCubeTransforms[3].SetPosition(KumaGL::Vec3(0, -2, -10));
    mCubeTransforms[4].SetPosition(KumaGL::Vec3(-2, 0, -10));
  }

  void Update() {
    // Rotate each cube.
    for (auto &t : mCubeTransforms) {
      t.Rotate(1, 1, 0);
    }
  }

  void Render(const RenderInfo &aInfo) {
    // Copy the cube matrices to the instance buffer.
    std::vector<KumaGL::Mat4> matrices;
    for (auto &t : mCubeTransforms) {
      matrices.emplace_back(t.GetMatrix());
    }

    aInfo.mCubeMesh.mInstanceBuffer.CopyData(
        GL_ARRAY_BUFFER, matrices.size() * sizeof(KumaGL::Mat4),
        matrices.data(), GL_DYNAMIC_DRAW);

    // Draw the cubes.
    aInfo.mCubeShader.Bind();
    aInfo.mCubeMesh.DrawInstanced(matrices.size());
  }
};

/******************************************************************************/
void FramebufferSizeCallback(GLFWwindow *aWindow, int aWidth, int aHeight) {
  screenWidth = aWidth;
  screenHeight = aHeight;
  glViewport(0, 0, screenWidth, screenHeight);
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
  window = glfwCreateWindow(1280, 720, "shadows", nullptr, nullptr);
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

  RenderInfo info;
  info.Setup();

  Scene scene;
  scene.Setup();

  // Run until instructed to close.
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene.Update();
    scene.Render(info);
  }

  info.Delete();

  glfwTerminate();
  return 0;
}
