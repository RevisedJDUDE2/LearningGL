#include "vao.h"
#include <stdio.h>
#include <memory.h>

void VAO_SetStruct(VertexArrayObject_t* VAO, GLuint Count) {
  VertexArrayObject_t temp = { 0, Count };
  memcpy(VAO, &temp, sizeof(temp));
}

void VAO_Init(VertexArrayObject_t* VAO) {
  glGenVertexArrays(VAO->count, &VAO->id);
}

void VAO_Bind(VertexArrayObject_t* VAO) {
  glBindVertexArray(VAO->id);
}

void VAO_Unbind(VertexArrayObject_t* VAO) {
  glBindVertexArray(0);
}
