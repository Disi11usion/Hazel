//
// Created by 吴棋凡 on 2023/2/17.
//

#include "Shader.h"
#include "glad/glad.h"
#include "Hazel/Core/Log.h"
#include "glm/gtc/type_ptr.hpp"
namespace Hazel {
Shader::Shader(const std::string &vertex_src, const std::string &fragment_src)
    : rendererID_(glCreateProgram()) {
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  const char *vertexShaderSource = vertex_src.c_str();
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success = 0;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (success == 0) {
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // fragment shader
  const char *fragmentShaderSource = fragment_src.c_str();
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (success == 0) {
    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // link shaders
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (success == 0) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  rendererID_ = shaderProgram;
}
Shader::~Shader() { glDeleteProgram(rendererID_); }
void Shader::Bind() const { glUseProgram(rendererID_); }
void Shader::UnBind() const { glUseProgram(0); }
void Shader::UploadUniformMat4(const std::string &name, const glm::mat4 &matrix) const {
  GLint location = glGetUniformLocation(rendererID_, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
} // namespace Hazel
