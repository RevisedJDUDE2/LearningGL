#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include<GLFW/glfw3.h>

class Window {
protected:
  Window(GLFWwindow* val) : val_(val) {};
  static Window* window_;
  GLFWwindow* val_;
public:
  Window(Window& other) = delete;

};

#endif