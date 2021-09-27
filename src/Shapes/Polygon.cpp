#include "Shapes/Polygon.h"

#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>

Polygon::Polygon(Vector2f pos, float radius, unsigned int vertexCount, Color color) : m_x(pos.getX()), m_y(pos.getY()), m_radius(radius), m_vertexCount(vertexCount), m_r(color.getRed()), m_g(color.getGreen()), m_b(color.getBlue()), m_shader(FileManager::getShader("Color/vertexShader.glsl"), FileManager::getShader("Color/fragmentShader.glsl"))
{
  vertices.push_back(m_x);
  vertices.push_back(m_y);
  vertices.push_back(0.f);
  vertices.push_back(m_r);
  vertices.push_back(m_g);
  vertices.push_back(m_b);

  for(int i = 0; i < m_vertexCount; i++)
  {
    // position
    vertices.push_back(m_x + (m_radius * cosf(i * (M_PI * 2) / m_vertexCount)));
    vertices.push_back(m_y + (m_radius * sinf(i * (M_PI * 2) / m_vertexCount)));
    vertices.push_back(0.f);
    
    // color
    vertices.push_back(m_r);
    vertices.push_back(m_g);
    vertices.push_back(m_b);

    indices.push_back(i+1);
    indices.push_back(0);
    if(i+2 > m_vertexCount)
      indices.push_back(1);
    else
      indices.push_back(i+2);
  }

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

void Polygon::move(GLFWwindow *window)
{
  double mouseX, mouseY;
  if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
  {
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glfwGetCursorPos(window, &mouseX, &mouseY);
    mouseX = -1.f + 2.f*mouseX / windowWidth;
    mouseY = 1.f - 2.f*mouseY / windowHeight;
    if(mouseX < m_x + m_radius && mouseX > m_x - m_radius && mouseY < m_y + m_radius && mouseY > m_y - m_radius)
    {
      m_x = mouseX;
      m_y = mouseY;
    }
  }
}

void Polygon::draw(GLFWwindow *window)
{
  move(window);

  vertices[0] = m_x, vertices[1] = m_y;
  for(int i = 0; i < m_vertexCount; i++)
  {
    vertices[(i*6)+6] = m_x + (m_radius * cosf(i * (M_PI * 2) / m_vertexCount));
    vertices[(i*6)+7] = m_y + (m_radius * sinf(i * (M_PI * 2) / m_vertexCount));
  }
  
  m_shader.use();
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, m_vertexCount*3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

Vector2f Polygon::getPosition() { return Vector2f(m_x, m_y); }

float Polygon::getRadius() { return m_radius; }
