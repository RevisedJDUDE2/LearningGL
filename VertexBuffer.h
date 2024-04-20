#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexBuffer {
private:
  GLuint mVbo;
public:
  VertexBuffer(GLsizeiptr size, const GLvoid* data);
  void Bind();
  void Unbind();
};

#endif