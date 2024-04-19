#undef _CONSOLE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
    //              COORDS              COLOR
    /*VERTEX1*/    -0.5, -0.5, 0.0f,   1.0f, 0.0f, 0.0f,
    /*VERTEX2*/     0.5, -0.5, 0.0f,   0.0f, 1.0f, 0.0f,
    /*VERTEX3*/     0.5,  0.5, 0.0f,   0.0f, 0.0f, 1.0f,
    /*VERTEX4*/    -0.5,  0.5, 0.0f,   1.0f, 1.0f, 0.0f
  };

  unsigned int Indices[] = {
    0, 1, 2,
    0, 2, 3
  };

  GLuint VBO, VAO, EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), &Vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), &Indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);


  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glViewport(0, 0, 800, 600);
  glfwSwapInterval(0);
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(Program);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, Indices);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    //ok!
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}