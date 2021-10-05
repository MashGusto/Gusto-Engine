#pragma once

/**
 * The shader class that is implemented for each graphical component.
 *
 * It contains a shader program that can be run to render a texture or color on to the graphical component.
 */

#include "Components/FileManager.h"

#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Shader
{
private:
  unsigned int program;
  unsigned int vertexShader;
  unsigned int fragmentShader;
  unsigned int compileShader(unsigned int type, const std::string &source);

public:
  static glm::mat4 projection;

  Shader(std::string shaderPath);
  void use();
  unsigned int getID();
};
