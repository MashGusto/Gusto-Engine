#pragma once

/**
 * The shader class that is implemented for each graphical component.
 *
 * It contains a shader program that can be run to render a texture or color on to the graphical component.
 */

#include "Components/FileManager.h"

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
