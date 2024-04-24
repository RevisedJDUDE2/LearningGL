#ifndef VAO_H
#define VAO_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vec3.h>
#include <vec2.h>

typedef struct Vertices {
  vec3 position[3];
  vec3 color;
} Vertices_t;


typedef struct VertexArrayObject {
  GLuint id;
  GLuint count;
} VertexArrayObject_t;

void VAO_SetStruct(VertexArrayObject_t* VAO, GLuint Count);
void VAO_Init(VertexArrayObject_t* VAO);
void VAO_Bind(VertexArrayObject_t* VAO);
void VAO_Unbind(VertexArrayObject_t* VAO);

void Vertices_Set(int index, Vertices_t* where, vec3 what);
void Vertices_AttributePointer(int index, int count, int stride, int offset);
#endif