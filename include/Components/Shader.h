#pragma once

#include <string>

class Shader
{
  private:
    unsigned int program;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int compileShader(unsigned int type, const std::string &source);
  public:
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
    void use();
};
