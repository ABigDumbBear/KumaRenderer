#ifndef RENDERBUFFER_HPP
#define RENDERBUFFER_HPP

#include <glad/glad.h>

namespace KumaGL {
class Renderbuffer {
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

  GLuint GetID() const { return mID; }

private:
  GLuint mID{0};
};
} // namespace KumaGL

#endif // !RENDERBUFFER_HPP
