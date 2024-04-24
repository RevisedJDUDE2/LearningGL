#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>

struct __Vertex {
  std::array<glm::vec3, 4> Position;
  glm::vec4 color;
  glm::vec2 textcoord;
};

class VertexArray {
private:
  GLuint mVAO;
public:
  VertexArray(void);
  void Bind();
  void Unbind();
};

#endif