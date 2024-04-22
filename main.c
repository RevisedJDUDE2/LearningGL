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
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  Buffer_t VBO;
  VBO.target = GL_VERTEX_ARRAY;
  VBO.size = sizeof(Vertices);
  VBO.data = &Vertices;
  VBO.usage = GL_STATIC_DRAW;
  Buffer_CreateBuffer(&VBO);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(Vertices), (void*)0);
  glEnableVertexAttribArray(0);

  Buffer_Unbind(&VBO);

  glBindVertexArray(0);

  while (!glfwWindowShouldClose(Window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(Window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}