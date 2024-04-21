#include "Shader.h"
#include <cstring>

void ShaderError(GLuint Shader, const char* ShaderType) {
  memset(mshdrInfLog, '\0', sizeof(mshdrInfLog)); //i forgot this crucial thing!
  glGetShaderiv(Shader, GL_COMPILE_STATUS, &mshdrCompStatus);
  if (!mshdrCompStatus) {
    glGetShaderInfoLog(Shader, 910, nullptr, mshdrInfLog);
    std::cout << ShaderType << ": Failed to compile: \n" << mshdrInfLog << "\n";
  }
}

std::string Shader::ReadShaderFile(const char * filename) {
  std::ifstream file(filename);
  if (file.is_open()) {
    std::stringstream shaderStream;
    shaderStream << file.rdbuf();
    file.close();
    return shaderStream.str();
  } else {
    std::cout << "Failed to open file: " << filename << " \n";
    return "";
  }
}

GLuint Shader::CreateShader(GLenum type, const char * source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  this->mShdrID = shader;
  return shader;
}

GLuint Shader::CreateProgram() {
  GLuint prog = glCreateProgram();
  this->mShdrID = prog;
  return prog;
}

void Shader::AttachProgram(GLuint ShdrID) {
  glAttachShader(this->mShdrID, ShdrID);
}

void Shader::LinkProgram() {
  glLinkProgram(this->mShdrID);
}

void Shader::UseProgram() {
  glUseProgram(this->mShdrID);
}

GLuint Shader::GetID(void) const {
  return this->mShdrID;
}
