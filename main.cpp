//#define SHADER_USE_FUNCTIONS
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

//My Headers
#include "CoreAPI.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include "Window.h"

int main() {
  Shader refVertex = {};
  PUSH_SHADER_SOURCE(refVertex, "./shader.vert");
  const char* VertexshdrSource = GET_SHADER_STRING(0);

  Shader refFragment = {};
  PUSH_SHADER_SOURCE(refFragment, "./shader.frag");
  const char* FragmentshdrSource = GET_SHADER_STRING(1);

  InitGLFW();
  Window::GetInstance().CreateWindow();
  glfwMakeContextCurrent(Window::GetInstance().GetWindow());
  InitGLEW();

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
  glfwSwapInterval(0);
  while ( !glfwWindowShouldClose(Window::GetInstance().GetWindow()) ) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glUseProgram(Prg);
    VAO.Bind();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, Indices);
    if (glfwGetKey( Window::GetInstance().GetWindow() , GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      break;
    }
    glfwSwapBuffers( Window::GetInstance().GetWindow() );
    glfwPollEvents();
  }
  VAO.Unbind();
  glDeleteProgram(Prg);
  glfwTerminate();
  return 0;
}