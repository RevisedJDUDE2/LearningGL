#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"

int main() {
  Shader refVertex;
  std::string vshSource = refVertex.ReadShaderFile("./shader.vert");
  const char* VertexshdrSource = vshSource.c_str();

  Shader refFragment;
  std::string fshSource = refFragment.ReadShaderFile("./shader.frag");
  const char* FragmentshdrSource = fshSource.c_str();

  if (!glfwInit())
    return -1;
  GLFWmonitor* ccMonitor = glfwGetPrimaryMonitor();
  GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL!", ccMonitor, nullptr);
  if (!window) {
    std::cout << "Window Failed!" << std::endl;
    return -1;
  }
  glfwMakeContextCurrent(window);
  if (glewInit() != GLEW_OK) {
    glfwTerminate();
  }

  GLuint Vertex = refVertex.CreateShader(GL_VERTEX_SHADER, VertexshdrSource);
  ShaderError(Vertex, "VertexShader");
  GLuint Fragment = refFragment.CreateShader(GL_FRAGMENT_SHADER, FragmentshdrSource);
  ShaderError(Fragment, "FragmentShader");

  Shader Programm;
  GLuint Prg = Programm.CreateProgram();
  Programm.AttachProgram(refVertex.GetID());
  Programm.AttachProgram(refFragment.GetID());
  Programm.LinkProgram();
  ShaderError(Prg, "Program");
  Programm.UseProgram();
  glDeleteProgram(Prg);

  glDeleteShader(Vertex);
  glDeleteShader(Fragment);

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
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(Prg);
    VAO.Bind();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, Indices);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      break;
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  VAO.Unbind();
  glDeleteProgram(Prg);
  glfwTerminate();
  return 0;
}