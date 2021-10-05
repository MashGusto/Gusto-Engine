#pragma once

/**
 * A graphical component, that is used to draw a polygon at a given position, with a given number of vertices, drawn with a given color.
 */

#include "Components/Texture.h"
#include "Components/Shader.h"
#include "Components/FileManager.h"
#include "Containers/Color.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>
#include <string>

class Polygon
{
private:
  glm::vec2 position;
  Color color;
  float radius;
  unsigned int vertexCount;
  Shader shader;
  unsigned int vbo;
  unsigned int vao;
  unsigned int ebo;
  std::vector<float> vertices;
  std::vector<unsigned int> indices;

public:
  Polygon(glm::vec2 Position, float Radius, unsigned int VertexCount, Color Color);
  glm::vec2 getPosition();
  float getRadius();
  void checkMovement(GLFWwindow *window);
  void draw(GLFWwindow *window);
};
