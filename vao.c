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

void Vertices_Set(int index, Vertices_t* where, vec3 what) {
  if (index == 0) {
    glm_vec3_copy(what, &where->position);
  };
  if (index == 1) {
    glm_vec3_copy(what, &where->color);
  };
}

void Vertices_AttributePointer(int index, int count, int stride, int offset) {
  glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset));
  glEnableVertexAttribArray(index);
}
