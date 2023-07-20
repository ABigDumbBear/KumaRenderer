#ifndef RENDERBUFFER_HPP
#define RENDERBUFFER_HPP

#include <glad/glad.h>

#include "KumaGL/GLObject.hpp"

namespace KumaGL {
class Renderbuffer : public GLObject {
public:
  Renderbuffer();
  ~Renderbuffer();
  Renderbuffer(Renderbuffer &&aBuffer);
  Renderbuffer &operator=(Renderbuffer &&aBuffer);
  Renderbuffer(const Renderbuffer &) = delete;
  Renderbuffer &operator=(const Renderbuffer &) = delete;

  void Generate();
  void Delete();
  void Bind();
  void Unbind();

  void SetStorageParameters(GLenum aStorageFormat, GLsizei aWidth,
                            GLsizei aHeight);
};
} // namespace KumaGL

#endif // !RENDERBUFFER_HPP
