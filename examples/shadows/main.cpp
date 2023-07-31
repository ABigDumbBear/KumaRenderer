#include "KumaGL/Mat4.hpp"
#include "KumaGL/Vec3.hpp"
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
int windowWidth = 1280;
int windowHeight = 720;

/******************************************************************************/
struct RenderInfo {
  KumaGL::Shader mCubeShader;
  KumaGL::Shader mDepthShader;
  KumaGL::Shader mDebugShader;

  KumaGL::Texture mCubeDiffuse;
  KumaGL::Texture mCubeSpecular;
  KumaGL::Texture mShadowMap;

  KumaGL::Mesh mCubeMesh;
  KumaGL::Mesh mQuadMesh;
  KumaGL::Mesh mDebugMesh;

  KumaGL::Framebuffer mShadowBuffer;

  void Setup() {
    // Configure the shaders.
    mCubeShader.LoadFromFiles("resources/shaders/Shader.vert",
                              "resources/shaders/Shader.frag");

    mCubeShader.SetInt("diffuseTexture", 0);
    mCubeShader.SetInt("specularTexture", 1);
    mCubeShader.SetInt("shadowMapTexture", 2);

    mCubeShader.SetVec3("lightColor", KumaGL::Vec3(1, 0.9, 0.7));
    mCubeShader.SetVec3("viewPos", KumaGL::Vec3(0, 0, 0));

    mCubeShader.SetFloat("shininess", 256);

    mDepthShader.LoadFromFiles("resources/shaders/DepthShader.vert",
                               "resources/shaders/DepthShader.frag");

    mDebugShader.LoadFromFiles("resources/shaders/DebugShader.vert",
                               "resources/shaders/DebugShader.frag");
    mDebugShader.SetInt("shadowMap", 2);

    // Configure the textures.
    mCubeDiffuse.LoadFromFile("resources/textures/diffuse.png");
    mCubeDiffuse.SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    mCubeDiffuse.SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    mCubeSpecular.LoadFromFile("resources/textures/specular.png");
    mCubeSpecular.SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    mCubeSpecular.SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    mShadowMap.LoadFromData(nullptr, 1280, 720, GL_DEPTH_COMPONENT, GL_FLOAT);
    mShadowMap.SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    mShadowMap.SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    mCubeDiffuse.Bind(GL_TEXTURE0);
    mCubeSpecular.Bind(GL_TEXTURE1);
    mShadowMap.Bind(GL_TEXTURE2);

    // Configure the meshes.
    mCubeMesh.InitCube();
    mQuadMesh.InitQuad();
    mDebugMesh.InitQuad();

    // Configure the framebuffer.
    mShadowBuffer.AttachTexture(mShadowMap, GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
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
    mShadowMap.Delete();
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
    mPlaneTransform.Scale(15, 15, 1);
    mPlaneTransform.Translate(KumaGL::Vec3(0, 0, -20));

    mLightTransform.Translate(KumaGL::Vec3(0, 0, 10));

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

  void PreRender(const RenderInfo &aInfo) {
    // Copy the cube matrices to the instance buffer.
    std::vector<KumaGL::Mat4> matrices;
    for (auto &t : mCubeTransforms) {
      matrices.emplace_back(t.GetMatrix());
    }

    aInfo.mCubeMesh.mInstanceBuffer.CopyData(
        GL_ARRAY_BUFFER, matrices.size() * sizeof(KumaGL::Mat4),
        matrices.data(), GL_DYNAMIC_DRAW);

    // Copy the plane matrix to the instance buffer.
    aInfo.mQuadMesh.mInstanceBuffer.CopyData(
        GL_ARRAY_BUFFER, sizeof(KumaGL::Mat4), &mPlaneTransform.GetMatrix(),
        GL_STATIC_DRAW);
  }

  void Render(const RenderInfo &aInfo) {
    aInfo.mCubeMesh.DrawInstanced(mCubeTransforms.size());
    aInfo.mQuadMesh.DrawInstanced(1);
  }
};

/******************************************************************************/
void FramebufferSizeCallback(GLFWwindow *aWindow, int aWidth, int aHeight) {
  windowWidth = aWidth;
  windowHeight = aHeight;
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

    // Update the scene.
    scene.Update();

    // Before rendering, copy scene data to the GPU.
    scene.PreRender(info);

    // For the first render pass, generate a depth map by rendering the scene
    // from the light's perspective and storing it in a texture.
    info.mShadowBuffer.Bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, info.mShadowMap.GetWidth(), info.mShadowMap.GetHeight());

    // Calculate the view and projection matrices for the light.
    auto lightView = KumaGL::View(scene.mLightTransform.GetForward(),
                                  scene.mLightTransform.GetRight(),
                                  scene.mLightTransform.GetWorldPosition());
    auto lightProj = KumaGL::Orthographic(-10, 10, -10, 10, 0.1, 100);

    // Set the shader uniforms.
    info.mDepthShader.SetMat4("viewMatrix", lightView);
    info.mDepthShader.SetMat4("projectionMatrix", lightProj);

    // Render to the shadow framebuffer.
    info.mDepthShader.Bind();
    scene.Render(info);
    info.mShadowBuffer.Unbind();

    /*
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, windowWidth, windowHeight);
    info.mDebugShader.Bind();
    info.mDebugMesh.DrawInstanced(1);
    */

    // For the second render pass, draw the scene as per usual from the viewer's
    // perspective.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, windowWidth, windowHeight);

    // Set the shader uniforms.
    info.mCubeShader.SetMat4("viewMatrix", KumaGL::View(KumaGL::Vec3(0, 0, 1),
                                                        KumaGL::Vec3(1, 0, 0),
                                                        KumaGL::Vec3(0, 0, 0)));
    info.mCubeShader.SetMat4("projectionMatrix",
                             KumaGL::Perspective(45, 1280, 720, 0.1, 100));
    info.mCubeShader.SetMat4("lightSpaceMatrix", lightProj * lightView);

    info.mCubeShader.SetVec3("lightPos",
                             scene.mLightTransform.GetWorldPosition());

    // Render the scene.
    info.mCubeShader.Bind();
    scene.Render(info);
    info.mCubeShader.Unbind();
  }

  info.Delete();

  glfwTerminate();
  return 0;
}
