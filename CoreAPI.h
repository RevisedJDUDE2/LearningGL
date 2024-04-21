#ifndef CoreAPI_H
#define CoreAPI_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void InitGLFW() {
  if (!glfwInit()) {
    glfwTerminate();
  }
}

void InitGLEW() {
  if (glewInit() != GLEW_OK) {
    glfwTerminate();
  }
}

#endif
