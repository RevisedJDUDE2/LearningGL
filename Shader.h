#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

static int mshdrCompStatus;
static char mshdrInfLog[910];

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
  void DeleteShader(void);
  void DeleteProgram(void);
};

#ifndef SHADER_USE_FUNCTIONS //idk why i did this
static std::vector<std::string> ShaderSourceArray;
#define PUSH_SHADER_SOURCE(shaderInstance, name) ShaderSourceArray.push_back(shaderInstance.ReadShaderFile(name))
#define GET_SHADER_STRING(index) ShaderSourceArray[index].c_str()
#else
int shdr;
static std::vector<std::string> ShaderSourceArray; //min size of shader sources!
void PUSH_SHADER_SOURCE(Shader Instance, const char* name) {
  ShaderSourceArray.push_back(Instance.ReadShaderFile(name));
}
const char* GET_SHADER_STRING(int index) {
  return ShaderSourceArray[index].c_str();
}
#endif

void ShaderError(GLuint Shader, const char* ShaderType);

#endif