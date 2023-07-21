#ifndef VAO_HPP
#define VAO_HPP

#include "GLObject.hpp"

namespace KumaGL {
class VAO : public GLObject {
public:
  VAO();
  ~VAO();
  VAO(VAO &&);
  VAO &operator=(VAO &&);
  VAO(const VAO &) = delete;
  VAO &operator=(const VAO &) = delete;

  void Generate();
  void Delete();
  void Bind();
  void Unbind();

  void ConfigureVertexAttribute();
};
} // namespace KumaGL

#endif // !VAO_HPP
