#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

#ifndef READ_SUCCESS
#include <vector>
static int mshdrCompStatus;
static char mshdrInfLog[910];
static std::vector<std::string> ShaderSourceArray;
#define PUSH_SHADER_SOURCE(shaderInstance, name) ShaderSourceArray.push_back(shaderInstance.ReadShaderFile(name))
#else
int shdr;
#endif

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