#include "Window.h"

void Window_Create(Window_t* win) {
  if (!win->currentmonitor) {
    win->currentmonitor = NULL;
  }
  GLFWwindow* Window_temp = glfwCreateWindow(win->width, win->height, win->title, win->currentmonitor, NULL);
  if (!Window_temp) {
    printf("Window was NULL\n");
  }
  win->window = Window_temp;
  glfwMakeContextCurrent(win->window);
}

GLFWwindow* Window_GetHandle(Window_t* win) {
  return win->window;
}

void Window_initialize_GLEW(void) {
  if (glewInit() != GLEW_OK) {
    printf("cannot initialize glew\n");
  }
}

void Window_Initialize_GLFW(void) {
  if (!glfwInit()) {
    printf("Cannot initialize glfw\n");
  }
};
