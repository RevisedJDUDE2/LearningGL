#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexArray {
private:
  GLuint mVAO;
public:
  VertexArray(void);
  void Bind();
  void Unbind();
};

#endif