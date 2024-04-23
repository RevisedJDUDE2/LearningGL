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
#include "stb/stb_image.h"

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
  //glDeleteProgram(Prg);
  Programm.DeleteProgram();

  //glDeleteShader(Vertex);
  refVertex.DeleteShader();
  //glDeleteShader(Fragment);
  refFragment.DeleteShader();

  float Vertices[] = {
    //                                COORDS              COLOR         IMAGE COORDS
    /*VERTEX1 ALSO 0 index*/     -0.5, -0.5, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    /*VERTEX2 ALSO 1 index*/      0.5, -0.5, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    /*VERTEX3 ALSO 2 index*/      0.5,  0.5, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    /*VERTEX4* ALSO 3 index*/    -0.5,  0.5, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
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

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); 
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  EBO.Unbind();
  VBO.Unbind();
  VAO.Unbind();

  int ImgW, ImgH, numColCh;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* bytes = stbi_load("./img.jpg", &ImgW, &ImgH, &numColCh, 0);

  GLuint texture;
  glGenTextures(1, &texture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ImgW, ImgH, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(bytes);
  glBindTexture(GL_TEXTURE_2D, 0);

  GLuint tex0uni = glGetUniformLocation(Prg, "tex0");
  Programm.UseProgram();
  glUniform1f(tex0uni, 0);

  while ( !glfwWindowShouldClose(Window::GetInstance().GetWindow()) ) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glUseProgram(Prg);
    glBindTexture(GL_TEXTURE_2D, texture);
    VAO.Bind();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, Indices, 1);
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