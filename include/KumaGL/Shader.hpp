#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glad/glad.h>

#include "KumaGL/GLObject.hpp"
#include "Mat4.hpp"
#include "Vec3.hpp"

namespace KumaGL {
class Shader : public GLObject {
public:
  Shader();
  ~Shader();
  Shader(Shader &&aShader);
  Shader &operator=(Shader &&aShader);
  Shader(const Shader &aShader) = delete;
  Shader &operator=(const Shader &aShader) = delete;

  void Generate();
  void Delete();
  void Bind();
  void Unbind();

  void LoadFromFiles(const std::string &aVertexFile,
                     const std::string &aFragmentFile);
  void LoadFromSource(const std::string &aVertexSource,
                      const std::string &aFragmentSource);

  void SetInt(const std::string &aName, int aValue);
  void SetFloat(const std::string &aName, float aValue);
  void SetVec3(const std::string &aName, const Vec3 &aValue);
  void SetMat4(const std::string &aName, const Mat4 &aValue);

private:
  enum class ShaderType { eVERTEX, eFRAGMENT };

  void CompileShader(unsigned int &aID, const std::string &aSource,
                     ShaderType aType);
  void LinkProgram(unsigned int aVertexID, unsigned int aFragmentID);
};
} // namespace KumaGL

#endif // !SHADER_HPP
