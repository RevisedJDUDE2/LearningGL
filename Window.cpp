#include "Window.h"
#include <iostream>

void Window::CreateWindow() {
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  mWindow = glfwCreateWindow(800, 600, "OpenGL!", nullptr, nullptr);
  if (!mWindow) {
    std::cout << "Window Creation Failed" << std::endl;
  }
}

GLFWwindow* Window::GetWindow() {
  return mWindow;
}
