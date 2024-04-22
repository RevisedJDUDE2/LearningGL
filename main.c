#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

//My headers
#include "Buffer.h"

int main() {
  if (!glfwInit()) {
    printf("Failed to initialize glfw");
    glfwTerminate();
    return -1;
  }
  GLFWwindow* Window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
  glfwMakeContextCurrent(Window);
  if (glewInit() != GLEW_OK) {
    printf("Glew init failure");
    glfwTerminate();
    return -1;
  }

  float Vertices[9] = {
    -0.5f, -0.5f, 0.0f,
     0.0f, 0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
  };

  Buffer_t VBO;
  VBO.count = 1;
  VBO.target = GL_VERTEX_ARRAY;
  VBO.size = sizeof(Vertices);
  VBO.data = &Vertices;
  VBO.usage = GL_STATIC_DRAW;
  Buffer_CreateBuffer(&VBO);

  Buffer_Unbind(&VBO);

  while (!glfwWindowShouldClose(Window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(Window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}