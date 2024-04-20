#include "Shader.h"

void ShaderError(GLuint Shader, const char* ShaderType) {
  glGetShaderiv(Shader, GL_COMPILE_STATUS, &mshdrCompStatus);
  if (!mshdrCompStatus) {
    glGetShaderInfoLog(Shader, 910, nullptr, mshdrInfLog);
    std::cout << ShaderType << ": Failed to compile: \n" << mshdrInfLog << "\n";
  }
}
