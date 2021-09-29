#pragma once

/**
 * A graphical component, that is used to draw a polygon at a given position, with a given number of vertices, drawn with a given color.
 */

#include "Components/Texture.h"
#include "Components/Shader.h"
#include "Components/FileManager.h"
#include "Math/Vector.h"
#include "Math/Color.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

class Polygon
{
  private:
    Vector2f m_position;
    Color m_color;
    float m_radius;
    unsigned int m_vertexCount;
    Shader m_shader;
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

  public:
    Polygon(Vector2f pos, float radius, unsigned int vertexCount, Color color);
    Vector2f getPosition();
    float getRadius();
    void move(GLFWwindow *window);
    void draw(GLFWwindow *window);
};
