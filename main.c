//#define SHADER_USE_FUNCTIONS
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

//My Headers
#include "CoreAPI.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include "Window.h"

int main() {
  float Vertices[] = {
    //                                COORDS              COLOR
    /*VERTEX1 ALSO 0 index*/     -0.5, -0.5, 0.0f,   1.0f, 0.0f, 0.0f, 
    /*VERTEX2 ALSO 1 index*/      0.5, -0.5, 0.0f,   0.0f, 1.0f, 0.0f,
    /*VERTEX3 ALSO 2 index*/      0.5,  0.5, 0.0f,   0.0f, 0.0f, 1.0f,
    /*VERTEX4* ALSO 3 index*/    -0.5,  0.5, 0.0f,   1.0f, 1.0f, 0.0f
  };

  unsigned int Indices[] = {
    0, 1, 2,
    0, 2, 3
  };
  return 0;
}