#undef _CONSOLE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "VertexBuffer.h"
#include "VertexArray.h"

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

  int success;
  char infoLog[912];

  GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(VertexShader, 1, &VertexShaderSource, NULL);
  glCompileShader(VertexShader);

  glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(VertexShader, 912, nullptr, infoLog);
    std::cout << "ERROR::VERTEXSHADER : " << infoLog << std::endl;
  }

  GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(FragmentShader, 1, &FragmentShaderSource, NULL);
  glCompileShader(FragmentShader);

  glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(FragmentShader, 912, nullptr, infoLog);
    std::cout << "ERROR::FRAGMENTSHADER : " << infoLog << std::endl;
  }

  GLuint Program = glCreateProgram();
  glAttachShader(Program, VertexShader);
  glAttachShader(Program, FragmentShader);
  glLinkProgram(Program);

  glGetShaderiv(Program, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(Program, 912, nullptr, infoLog);
    std::cout << "ERROR::SHADERPROGRAM : " << infoLog << std::endl;
  }

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
  //TELLING opengl which vertices / vec coords to render again
  // so.. 0 index, 1 index, etc
  //but we have and 4 or 3 index which is the new point so we add 0, 2, 3 thus a rectangle / quad!

  GLuint EBO;


  VertexArray VAO;
  glGenBuffers(1, &EBO);
  //make vao then put and vbo on an vao and put ebo in vbo in vao...
  // VAO = VBO
  // VBO has a EBO or VBO and EBO is stored in a VAO
  
  VAO.Bind();

  VertexBuffer VBO(sizeof(Vertices), &Vertices);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  //WE tell opengl that we are currently selecting an EBO
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), &Indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  //the stride is how much items on an vertex... x, y, z,   r, g, b so 6 * sizeof(float)
  //because it accepts it as size but in bytes!
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); 
  //the offset is how much bytes to go to the second attrubute ex... rgb is 3 * sizeof(float) because 3 is coordinate
  //and we want to go to rgb so we multiply the coordinate(s) by 3 (xyz)
  glEnableVertexAttribArray(1);


  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  VAO.Unbind();

  glViewport(0, 0, 800, 600);
  glfwSwapInterval(0);
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(Program);
    VAO.Bind();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, Indices);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}