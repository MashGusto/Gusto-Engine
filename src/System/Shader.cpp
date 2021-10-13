#include "System/Shader.h"

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// Including headers for alloca function
// Solution from https://github.com/ocornut/imgui/issues/1917#issuecomment-401591478
#if defined(__CYGWIN__)
#include <alloca.h> // alloca
#endif              //__CYGWIN__
#if !defined(alloca)
#ifdef _WIN32
#include <malloc.h> // alloca
#if !defined(alloca)
#define alloca _alloca // for clang with MS Codegen
#endif
#elif defined(__GLIBC__) || defined(__sun)
#include <alloca.h> // alloca
#else
#include <stdlib.h> // alloca
#endif
#endif

glm::mat4 Shader::projection = glm::ortho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
int Shader::projectionScale = 100;

// Constructor for the shader class.
// Takes in the file path to the vertex shader and the fragment shader.
// It compiles the glsl code and links the shader program.
// It deletes both shaders after validation of the program, as they are no longer needed.
Shader::Shader(std::string shaderPath)
{
  program = glCreateProgram();
  ShaderSource shaderFile = FileManager::readShader(shaderPath);
  vertexShader = compileShader(GL_VERTEX_SHADER, shaderFile.vertexSource);
  fragmentShader = compileShader(GL_FRAGMENT_SHADER, shaderFile.fragmentSource);
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);
  glValidateProgram(program);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glUseProgram(program);
}

// Compiles the shader, by creating a new shader of given type, and applying to it the given source code.
// It also looks for errors in the compilation.
// Returns an id to the shader.
unsigned int Shader::compileShader(unsigned int type, const std::string &source)
{
  unsigned int id = glCreateShader(type);
  const char *src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE)
  {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char *message = (char *)alloca(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
    std::cout << message << std::endl;
    glDeleteShader(id);
    return 0;
  }

  return id;
}

// Makes the current shader the one to apply on its parent graphical component.
void Shader::use()
{
  glUseProgram(program);
}

unsigned int Shader::getID()
{
  return program;
}

void Shader::setProjection(glm::mat4 Projection) { projection = Projection; }

glm::mat4 Shader::getProjection() { return projection; }

void Shader::setProjectionScale(int ProjectionScale)
{
  projectionScale = ProjectionScale;
  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  setProjection(glm::ortho((float)-mode->width / Shader::getProjectionScale(), (float)mode->width / Shader::getProjectionScale(), (float)-mode->height / Shader::getProjectionScale(), (float)mode->height / Shader::getProjectionScale(), -1.f, 1.f));
}

int Shader::getProjectionScale() { return projectionScale; }
