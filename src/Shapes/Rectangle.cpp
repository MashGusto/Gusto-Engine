#include "Shapes/Rectangle.h"

// Takes in the position, size and color of the rectangle shape, and assigns the values to their respective data members.
Rectangle::Rectangle(Vector2f pos, Vector2f size, Color color) : m_position(pos), m_size(size), m_color(color), m_shader(FileManager::getShader("Color/vertexShader.glsl"), FileManager::getShader("Color/fragmentShader.glsl"))
{
  // Set the vertices of the rectangle according to its position and size.

  // Positions
  vertices[0]  = m_position.getX(),                 vertices[1]  = m_position.getY(),                 vertices[2]  = 0.f;
  vertices[6]  = m_position.getX() + m_size.getX(), vertices[7]  = m_position.getY(),                 vertices[8]  = 0.f;
  vertices[12] = m_position.getX() + m_size.getX(), vertices[13] = m_position.getY() - m_size.getY(), vertices[14] = 0.f;
  vertices[18] = m_position.getX(),                 vertices[19] = m_position.getY() - m_size.getY(), vertices[20] = 0.f;
  
  // Colors
  vertices[3]  = m_color.getRed(), vertices[4]  = m_color.getGreen(), vertices[5]  = m_color.getBlue();
  vertices[9]  = m_color.getRed(), vertices[10] = m_color.getGreen(), vertices[11] = m_color.getBlue();
  vertices[15] = m_color.getRed(), vertices[16] = m_color.getGreen(), vertices[17] = m_color.getBlue();
  vertices[21] = m_color.getRed(), vertices[22] = m_color.getGreen(), vertices[23] = m_color.getBlue();

  // Generate buffers for the rectangle, and assign attributes to it, to be used by its shaders.
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

// Move the rectangle according to keyboard input(WASD)
void Rectangle::move(GLFWwindow *window)
{
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    m_position += Vector2f(0.f, 0.001f);
  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    m_position += Vector2f(-0.001f, 0.f);
  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    m_position += Vector2f(0.f, -0.001f);
  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    m_position += Vector2f(0.001f, 0.f);
}

// Draw the rectangle on to the screen, on the rectangle's current position.
// To be called each game frame.
void Rectangle::draw(GLFWwindow *window)
{
  // Takes in keyboard input, and calls the move function.
  move(window);

  // Repositions the vertices, according to current position.
  vertices[0]  = m_position.getX(),                 vertices[1]  = m_position.getY();
  vertices[6]  = m_position.getX() + m_size.getX(), vertices[7]  = m_position.getY();
  vertices[12] = m_position.getX() + m_size.getX(), vertices[13] = m_position.getY() - m_size.getY();
  vertices[18] = m_position.getX(),                 vertices[19] = m_position.getY() - m_size.getY();
  
  // Make the rectangle's shader the shader to use to draw it.
  m_shader.use();
  // Rebuffer the rectangle, and reassign the vertex attribute values.
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindVertexArray(vao);
  // Draw the rectangle.
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

// Returns a vector value of the current position of the rectangle.
Vector2f Rectangle::getPosition() { return m_position; }

// Returns a vector value of the size of the rectangle.
Vector2f Rectangle::getSize() { return m_size; }
