#include "Shapes/Polygon.h"

#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>

// Takes in the position, radius, number of vertices, and color of the polygon, and assigns those values to respective data members.
Polygon::Polygon(Vector2f pos, float radius, unsigned int vertexCount, Color color) : m_position(pos), m_radius(radius), m_vertexCount(vertexCount), m_color(color), m_shader(FileManager::getShader("Color/vertexShader.glsl"), FileManager::getShader("Color/fragmentShader.glsl"))
{
  // The center of the polygon
  vertices.push_back(m_position.getX());
  vertices.push_back(m_position.getY());
  vertices.push_back(0.f);
  vertices.push_back(m_color.getRed());
  vertices.push_back(m_color.getGreen());
  vertices.push_back(m_color.getBlue());

  for(int i = 0; i < m_vertexCount; i++)
  {
    // Setting the vertices according to its radius, and calculated using sin and cos.
    
    // position
    vertices.push_back(m_position.getX() + (m_radius * cosf(i * (M_PI * 2) / m_vertexCount)));
    vertices.push_back(m_position.getY() + (m_radius * sinf(i * (M_PI * 2) / m_vertexCount)));
    vertices.push_back(0.f);
    
    // color
    vertices.push_back(m_color.getRed());
    vertices.push_back(m_color.getGreen());
    vertices.push_back(m_color.getBlue());

    indices.push_back(i+1);
    indices.push_back(0);
    if(i+2 > m_vertexCount)
      indices.push_back(1);
    else
      indices.push_back(i+2);
  }

  // Generate buffers for the polygon shape, and assign position and color attributes to it, to be used by the shaders.
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &ebo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(float), &indices[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

// Move the polygon, by the method of dragging with mouse.
void Polygon::move(GLFWwindow *window)
{
  double mouseX, mouseY;
  // Checks if the left mouse button in held down, and the mouse pointer is inside the polygon shape.
  if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
  {
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glfwGetCursorPos(window, &mouseX, &mouseY);
    mouseX = -1.f + 2.f*mouseX / windowWidth;
    mouseY = 1.f - 2.f*mouseY / windowHeight;
    if(mouseX < m_position.getX() + m_radius && mouseX > m_position.getX() - m_radius && mouseY < m_position.getY() + m_radius && mouseY > m_position.getY() - m_radius)
    {
      m_position.setX(mouseX);
      m_position.setY(mouseY);
    }
  }
}

// Draws the polygon, at its current position.
// To be called each game frame.
void Polygon::draw(GLFWwindow *window)
{
  // Takes in mouse input, and calls the move function.
  move(window);
  
  // Repositions the vertices, according to current position.
  vertices[0] = m_position.getX(), vertices[1] = m_position.getY();
  for(int i = 0; i < m_vertexCount; i++)
  {
    vertices[(i*6)+6] = m_position.getX() + (m_radius * cosf(i * (M_PI * 2) / m_vertexCount));
    vertices[(i*6)+7] = m_position.getY() + (m_radius * sinf(i * (M_PI * 2) / m_vertexCount));
  }
  
  // Rebuffer the positions, and set its shader to be used to render the shape.
  m_shader.use();
  // Rebuffers the polygon, and reassigns the vertex attribute values.
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);
  glBindVertexArray(vao);
  // Draws the polygon.
  glDrawElements(GL_TRIANGLES, m_vertexCount*3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

// Get a vector value of the shape's current position.
Vector2f Polygon::getPosition() { return m_position; }

// Get the radius of the polygon.
float Polygon::getRadius() { return m_radius; }
