#include "VertexArray.h"

VertexArray::VertexArray(void) {
  glGenVertexArrays(1, &this->mVAO);
}

void VertexArray::Bind() {
  glBindVertexArray(this->mVAO);
}

void VertexArray::Unbind() {
  glBindVertexArray(0);
}
