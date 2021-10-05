#pragma once

/**
 * A graphical component, that is used to draw a rectangle at a given position, drawn with a given color.
 */

#include "Components/Texture.h"
#include "Components/Shader.h"
#include "Components/FileManager.h"

#include "Containers/Color.h"

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Rectangle
{
private:
  glm::vec2 position, scale;
  Color color;
  Shader shader;
  float vertices[24];

  // The arrangement of the vertices of the rectangle
  unsigned int indices[6] = {
      3, 0, 2,
      2, 0, 1};

  unsigned int vbo;
  unsigned int vao;
  unsigned int ebo;

public:
  Rectangle(glm::vec2 pos, glm::vec2 scale, Color color);
  glm::vec2 getPosition();
  glm::vec2 getScale();
  void checkMovement(GLFWwindow *window);
  void draw(GLFWwindow *window);
};
