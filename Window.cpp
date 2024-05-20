#include "Window.h"
#include <iostream>

void Window::CreateWindow() {
  glfwWindowHint(GLFW_SAMPLES, 16);
  mWindow = glfwCreateWindow(800, 600, "OpenGL!", nullptr, nullptr);
  if (!mWindow) {
    std::cout << "Window Creation Failed" << std::endl;
  }
  int* x, * y;
  x = nullptr;
  y = nullptr;
  glfwGetMonitorPos(glfwGetPrimaryMonitor(), NULL, NULL);
  std::cout << "X: " << x << "Y: " << y << std::endl;
  glfwSetWindowPos(mWindow, (int)1000/2, (int)100);
}

GLFWwindow* Window::GetWindow() {
  return mWindow;
}
