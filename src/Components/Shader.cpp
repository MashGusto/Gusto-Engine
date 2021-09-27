#include "Components/Shader.h"
#include "Components/FileManager.h"

#include <iostream>
#include <GL/glew.h>

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
  program = glCreateProgram();
  vertexShader = compileShader(GL_VERTEX_SHADER, FileManager::readFromFile(vertexShaderPath));
  fragmentShader = compileShader(GL_FRAGMENT_SHADER, FileManager::readFromFile(fragmentShaderPath));
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);
  glValidateProgram(program);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glUseProgram(program);
}

unsigned int Shader::compileShader(unsigned int type, const std::string &source)
{
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);
  
  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if(result == GL_FALSE)
  {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*) alloca(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
    std::cout << message << std::endl;
    glDeleteShader(id);
    return 0;
  }
  
  return id;
}

void Shader::use()
{
  glUseProgram(program);
}
