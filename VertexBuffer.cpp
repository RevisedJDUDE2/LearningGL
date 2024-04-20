#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(GLsizeiptr size, const GLvoid* data) {
  glGenBuffers(1, &this->mVbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->mVbo);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() {
  glBindBuffer(GL_VERTEX_ARRAY, this->mVbo);
}

void VertexBuffer::Unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

