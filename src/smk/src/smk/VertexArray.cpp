#include <smk/VertexArray.hpp>

namespace smk {

VertexArray::VertexArray() = default;
VertexArray::VertexArray(const std::vector<Vertex>& array) {
  size_ = array.size();
  glGenBuffers(1, &handle_);
  Bind();
  glBufferData(GL_ARRAY_BUFFER, array.size() * sizeof(Vertex), array.data(),
               GL_STATIC_DRAW);
  UnBind();
}

VertexArray::~VertexArray() {
  if (handle_)
    glDeleteBuffers(1, &handle_);
}

void VertexArray::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, handle_);
}

void VertexArray::UnBind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexArray::VertexArray(VertexArray&& other) {
  this->operator=(std::move(other));
}

void VertexArray::operator=(VertexArray&& other) {
  std::swap(handle_, other.handle_);
  std::swap(size_, other.size_);
}

} // namespace smk.
