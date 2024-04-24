#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

//My headers
#include "Buffer.h"
#include "vao.h"
#include "Window.h"

int main() {
  Window_Initialize_GLFW();
  Window_t winparams = { .width = 800, .height = 600, .title = "OpenGL" };
  Window_Create(&winparams);
  glfwMakeContextCurrent(Window_GetHandle(&winparams));
  Window_initialize_GLEW();
  glEnableVertexAttribArray(0);

  float Vertsices[9] = {
    -0.5f, -0.5f, 0.0f,
     0.0f, 0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
  };
  Vertices_t triangle = {
    .position[0] = {-0.5f, -0.5f, 0.0f},
    .position[1] = {0.0f, 0.5f, 0.0f},
    .position[2] = {0.5f, -0.5f, 0.0f}
  };
  VertexArrayObject_t VAO;
  VAO_SetStruct(&VAO, 1);
  Buffer_t VBO;
  Buffer_SetStruct(&VBO, 1, sizeof(triangle.position), triangle.position, GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  Buffer_Init(&VBO);
  VAO_Bind(&VAO);
  Buffer_CreateBuffer(&VBO);

  Vertices_AttributePointer(0, 3, 3 * sizeof(float), 0);

  Buffer_Unbind(&VBO);

  glBindVertexArray(0);
  VAO_Unbind(&VAO);

  while (!glfwWindowShouldClose(Window_GetHandle(&winparams))) {
    glClear(GL_COLOR_BUFFER_BIT);
    VAO_Bind(&VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(Window_GetHandle(&winparams));
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}