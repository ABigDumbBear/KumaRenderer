#ifndef VBO_HPP
#define VBO_HPP

#include <glad/glad.h>

namespace KumaGL {
class VBO {
public:
  VBO();
  ~VBO();
  VBO(VBO &&);
  VBO &operator=(VBO &&);
  VBO(const VBO &) = delete;
  VBO &operator=(const VBO &) = delete;

  void Generate();
  void Delete();
  void Bind(GLenum aTarget);
  void Unbind(GLenum aTarget);

  void CopyData(GLenum aTarget, GLsizeiptr aSize, const void *aData,
                GLenum aUsage);

  GLuint GetID() const { return mID; }

private:
  GLuint mID{0};
};
} // namespace KumaGL

#endif // !VBO_HPP
