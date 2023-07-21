#include "KumaGL/VAO.hpp"
#include "KumaGL/GLObject.hpp"

#include <algorithm>

namespace KumaGL {
/******************************************************************************/
VAO::VAO() { Generate(); }

/******************************************************************************/
VAO::~VAO() { Delete(); }

/******************************************************************************/
VAO::VAO(VAO &&aObject) : GLObject(std::move(aObject)) {}

/******************************************************************************/
VAO &VAO::operator=(VAO &&aObject) {
  Delete();
  GLObject::operator=(std::move(aObject));
  return *this;
}

/******************************************************************************/
void VAO::Generate() {
  if (!mID) {
    glGenVertexArrays(1, &mID);
  }
}

/******************************************************************************/
void VAO::Delete() {
  if (mID) {
    glDeleteVertexArrays(1, &mID);
    mID = 0;
  }
}

/******************************************************************************/
void VAO::Bind() { glBindVertexArray(mID); }

/******************************************************************************/
void VAO::Unbind() { glBindVertexArray(0); }
} // namespace KumaGL
