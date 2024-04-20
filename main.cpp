#undef _CONSOLE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"

int main() {

  const char* VertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
    "   ourColor = aColor;\n"
    "}\0";

  const char* FragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0f);\n"
    "}\0";

  if (!glfwInit())
    return -1;
  GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL!", nullptr, nullptr);
  if (!window) {
    std::cout << "Window Failed!" << std::endl;
    return -1;
  }
  glfwMakeContextCurrent(window);
  if (glewInit() != GLEW_OK) {
    glfwTerminate();
  }

  GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(VertexShader, 1, &VertexShaderSource, NULL);
  glCompileShader(VertexShader);

  ShaderError(VertexShader, "VertexShader");

  GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(FragmentShader, 1, &FragmentShaderSource, NULL);
  glCompileShader(FragmentShader);

  ShaderError(FragmentShader, "FragmentShader");

  GLuint Program = glCreateProgram();
  glAttachShader(Program, VertexShader);
  glAttachShader(Program, FragmentShader);
  glLinkProgram(Program);

  ShaderError(Program, "ProgramShader");

  glUseProgram(Program);

  glDeleteShader(VertexShader);
  glDeleteShader(FragmentShader);

  float Vertices[] = {
    //                                COORDS              COLOR
    /*VERTEX1 ALSO 0 index*/     -0.5, -0.5, 0.0f,   1.0f, 0.0f, 0.0f, 
    /*VERTEX2 ALSO 1 index*/      0.5, -0.5, 0.0f,   0.0f, 1.0f, 0.0f,
    /*VERTEX3 ALSO 2 index*/      0.5,  0.5, 0.0f,   0.0f, 0.0f, 1.0f,
    /*VERTEX4* ALSO 3 index*/    -0.5,  0.5, 0.0f,   1.0f, 1.0f, 0.0f
  };

  unsigned int Indices[] = {
    0, 1, 2,
    0, 2, 3
  };

  VertexArray VAO;
  ElementBuffer EBO;
  EBO.GenEBO();
  VAO.Bind();
  VertexBuffer VBO(sizeof(Vertices), &Vertices);
  EBO.Setup(sizeof(Indices), Indices);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); 
  glEnableVertexAttribArray(1);


  EBO.Unbind();
  VBO.Unbind();
  VAO.Unbind();

  glViewport(0, 0, 800, 600);
  glfwSwapInterval(0);
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(Program);
    VAO.Bind();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, Indices);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  VAO.Unbind();
  glDeleteProgram(Program);
  glfwTerminate();
  return 0;
}