#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

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
  while (!glfwWindowShouldClose(Window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(Window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}