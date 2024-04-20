#include "Shader.h"

void ShaderError(GLuint Shader, const char* ShaderType) {
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
  return std::string();
}
