//#define SHADER_USE_FUNCTIONS
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

void viewport_resize(GLFWwindow*, int w, int h);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

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
  glfwSetFramebufferSizeCallback(Window::GetInstance().GetWindow(), viewport_resize);
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
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  1.0f
  };

  unsigned int Indices[] = {
    0, 1, 2,
    0, 2, 3,
    4, 5, 6,
    2, 4, 0
  };

  VertexArray VAO;
  ElementBuffer EBO;
  EBO.GenEBO();
  VAO.Bind();
  VertexBuffer VBO(sizeof(Vertices), &Vertices);
  EBO.Setup(sizeof(Indices), Indices);
  //                                              sizeof(Vertex)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(6 * sizeof(float)));
  //glEnableVertexAttribArray(2);

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

  //GLuint tex0uni = glGetUniformLocation(Prg, "tex0");
  Programm.UseProgram();
  //glUniform1f(tex0uni, 0);
  float currenttime, delta;
  currenttime = (float)glfwGetTime();

  glEnable(GL_DEPTH_TEST);
  while (!glfwWindowShouldClose(Window::GetInstance().GetWindow())) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.6f, 1.0f, 1.0f);


    glm::mat4 transform = glm::mat4(1.0f);
    float newtile = (float)glfwGetTime();
    delta = newtile - currenttime;
    currenttime = newtile;
    if (glfwGetKey(Window::GetInstance().GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
      const float movement = 300.f;
      transform = glm::translate(transform, glm::vec3(movement * delta, 0.0f, 0.0f));
    }
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 projection = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
    if (glfwGetKey(Window::GetInstance().GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
      cameraPos -= 2.5f * delta * cameraFront;
    }
    if (glfwGetKey(Window::GetInstance().GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
      cameraPos += 2.5f * delta * cameraFront;
    }
    if (glfwGetKey(Window::GetInstance().GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
      cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * 2.5f * delta;
    }
    if (glfwGetKey(Window::GetInstance().GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
      cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * 2.5f * delta;
    }
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    unsigned int modelm = glGetUniformLocation(Prg, "model");
    unsigned int viewm = glGetUniformLocation(Prg, "view");
    unsigned int projectm = glGetUniformLocation(Prg, "projection");
    glUniformMatrix4fv(modelm, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewm, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(projectm, 1, GL_FALSE, &projection[0][0]);

    glUseProgram(Prg);
    GLuint trans = glGetUniformLocation(Prg, "trans");
    glUniformMatrix4fv(trans, 1, GL_FALSE, glm::value_ptr(transform));
    glBindTexture(GL_TEXTURE_2D, texture);
    VAO.Bind();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, 36);
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

void viewport_resize(GLFWwindow* window, int w, int h) {
  glViewport(0, 0, w, h);
}