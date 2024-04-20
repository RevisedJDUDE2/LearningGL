#include "ElementBuffer.h"

void ElementBuffer::GenEBO() {
  glGenBuffers(1, &this->mEBO);
}

void ElementBuffer::Setup(GLsizeiptr size, const GLvoid* data) {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void ElementBuffer::Bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mEBO);
}

void ElementBuffer::Unbind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
