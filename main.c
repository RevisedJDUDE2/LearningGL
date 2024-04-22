#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int main() {
  if (!glfwInit())
    glfwTerminate();
  if (glewInit() != GLEW_OK)
    glfwTerminate();
  return 0;
}