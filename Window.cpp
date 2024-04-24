#include "Window.h"
#include <iostream>

void Window::CreateWindow() {
  mWindow = glfwCreateWindow(800, 600, "OpenGL!", glfwGetPrimaryMonitor(), nullptr);
  if (!mWindow) {
    std::cout << "Window Creation Failed" << std::endl;
  }
}

GLFWwindow* Window::GetWindow() {
  return mWindow;
}
