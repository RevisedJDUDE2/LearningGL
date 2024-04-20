#ifndef ELEMENT_BUFFER_H
#define ELEMENT_BUFFER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ElementBuffer {
private:
  GLuint mEBO;
public:
  void GenEBO();
  void Setup(GLsizeiptr size, const GLvoid* data);
  void Bind();
  void Unbind();
};

#endif