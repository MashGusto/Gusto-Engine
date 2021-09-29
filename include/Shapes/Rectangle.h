#pragma once

/**
 * A graphical component, that is used to draw a rectangle at a given position, drawn with a given color.
 */

#include "Components/Texture.h"
#include "Components/Shader.h"
#include "Components/FileManager.h"
#include "Math/Vector.h"
#include "Math/Color.h"

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Rectangle
{
  private:
    Vector2f m_position, m_size;
    Color m_color;
    Shader m_shader;
    float vertices[24];

    // The arrangement of the vertices of the rectangle
    unsigned int indices[6] = {
      3, 0, 2,
      2, 0, 1
    };

    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
  
  public:
    Rectangle(Vector2f pos, Vector2f size, Color color);
    Vector2f getPosition();
    Vector2f getSize();
    void move(GLFWwindow *window);
    void draw(GLFWwindow *window);
};
