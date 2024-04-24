#ifndef VAO_H
#define VAO_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vec3.h>
#include <vec2.h>

typedef struct Vertices {
  vec3 position;
  vec2 color;
} Vertices_t;


typedef struct VertexArrayObject {
  GLuint id;
  GLuint count;
} VertexArrayObject_t;

void VAO_SetStruct(VertexArrayObject_t* VAO, GLuint Count);
void VAO_Init(VertexArrayObject_t* VAO);
void VAO_Bind(VertexArrayObject_t* VAO);
void VAO_Unbind(VertexArrayObject_t* VAO);

#endif