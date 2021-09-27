#include "Shapes/Rectangle.h"

Rectangle::Rectangle(Vector2f pos, Vector2f size, Color color) : m_x(pos.getX()), m_y(pos.getY()), m_width(size.getX()), m_height(size.getY()), m_r(color.getRed()), m_g(color.getGreen()), m_b(color.getBlue()), m_shader(FileManager::getShader("Color/vertexShader.glsl"), FileManager::getShader("Color/fragmentShader.glsl"))
{
  // Positions
  vertices[0]  = m_x,           vertices[1]  = m_y,            vertices[2]  = 0.f;
  vertices[6]  = m_x + m_width, vertices[7]  = m_y,            vertices[8]  = 0.f;
  vertices[12] = m_x + m_width, vertices[13] = m_y - m_height, vertices[14] = 0.f;
  vertices[18] = m_x,           vertices[19] = m_y - m_height, vertices[20] = 0.f;
  
  // Colors
  vertices[3]  = m_r, vertices[4]  = m_g, vertices[5]  = m_b;
  vertices[9]  = m_r, vertices[10] = m_g, vertices[11] = m_b;
  vertices[15] = m_r, vertices[16] = m_g, vertices[17] = m_b;
  vertices[21] = m_r, vertices[22] = m_g, vertices[23] = m_b;

  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &ebo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

void Rectangle::move(GLFWwindow *window)
{
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    m_y += 0.001f;
  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    m_x -= 0.001f;
  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    m_y -= 0.001f;
  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    m_x += 0.001f;
}

void Rectangle::draw(GLFWwindow *window)
{
  move(window);

  vertices[0] = m_x,           vertices[1] = m_y;
  vertices[6] = m_x + m_width, vertices[7] = m_y;
  vertices[12] = m_x + m_width, vertices[13] = m_y - m_height;
  vertices[18] = m_x,           vertices[19] = m_y - m_height;
  
  m_shader.use();
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

Vector2f Rectangle::getPosition() { return Vector2f(m_x, m_y); }

Vector2f Rectangle::getSize() { return Vector2f(m_width, m_height); }
