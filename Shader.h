#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#ifndef READ_SUCCESS
static int mshdrCompStatus;
static char mshdrInfLog[910];
#else
int shdr;
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>;

void ShaderError(GLuint Shader, const char* ShaderType);

class Shader {
private:
  GLuint mShdrID;
public:
  std::string ReadShaderFile(const char * filename);
  GLuint CreateShader(GLenum type, const char * source);
  GLuint CreateProgram();
  void AttachProgram(GLuint ShdrID);
  void LinkProgram();
  void UseProgram();
  GLuint GetID(void) const;
};

#endif