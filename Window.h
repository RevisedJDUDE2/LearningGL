#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
  Window(const Window&) = delete;

  static Window& GetInstance() {
    static Window Instance;
    return Instance;
  }

  void CreateWindow();

  GLFWwindow* GetWindow();

private:
  Window() {};

  GLFWwindow* mWindow;
};

#endif