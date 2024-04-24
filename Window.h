#ifndef WINDOW_H
#define WINDOW_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

typedef struct Window {
  int width, height;
  const char* title;
  GLFWmonitor* currentmonitor;
  GLFWwindow* window;
} Window_t;

void Window_Initialize_GLFW(void);
void Window_Create(Window_t* win);
GLFWwindow* Window_GetHandle(Window_t* win);
void Window_initialize_GLEW(void);

#endif // !WINDOW_H
