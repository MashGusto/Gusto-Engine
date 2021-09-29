#include "Sprites/Player.h"

// Takes in the position, size and texture of the movable sprite, and assigns the values to their respective data members.
Player::Player(Vector2f pos, Vector2f size, std::string textureImagePath, float textureImageScale) : m_position(pos), m_size(size), m_shader(FileManager::getShader("Texture/vertexShader.glsl"), FileManager::getShader("Texture/fragmentShader.glsl"))
{
  // Assigns the given texture's id to a data member of the sprite.
  Texture texture(textureImagePath);
  m_texture = texture.getTexture();
  
  // Set the positions of the vertices of the sprite according to its positions.

  // Positions
  vertices[0]  = m_position.getX(),                 vertices[1]  = m_position.getY(),                 vertices[2]  = 0.f;
  vertices[5]  = m_position.getX() + m_size.getX(), vertices[6]  = m_position.getY(),                 vertices[7]  = 0.f;
  vertices[10] = m_position.getX() + m_size.getX(), vertices[11] = m_position.getY() - m_size.getY(), vertices[12] = 0.f;
  vertices[15] = m_position.getX(),                 vertices[16] = m_position.getY() - m_size.getY(), vertices[17] = 0.f;
  
  // Texture Coordinates
  vertices[3]  = 0.f, vertices[4]  = 1.f;
  vertices[8]  = 1.f, vertices[9]  = 1.f;
  vertices[13] = 1.f, vertices[14] = 0.f;
  vertices[18] = 0.f, vertices[19] = 0.f;

  // Generate buffers for the sprite, assign the vertex values to attributes to be used by the shader.
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &ebo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

// Move the sprite according to keyboard input(WASD)
void Player::move(GLFWwindow *window)
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

// Draws the sprite to the window.
// To be called each game frame.
void Player::draw(GLFWwindow *window)
{
  // Takes in keyboard input, and calls the move function.
  move(window);
  
  // Reassigns the  vertex positions of the sprite, according to current position.
  vertices[0]  = m_position.getX(),                 vertices[1]  = m_position.getY();
  vertices[5]  = m_position.getX() + m_size.getX(), vertices[6]  = m_position.getY();
  vertices[10] = m_position.getX() + m_size.getX(), vertices[11] = m_position.getY() - m_size.getY();
  vertices[15] = m_position.getX(),                 vertices[16] = m_position.getY() - m_size.getY();
  
  // Make the sprite's shader the shader to use to draw it.
  m_shader.use();
  // Rebuffer the sprite, and reassign the vertex attribute values.
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
  glBindTexture(GL_TEXTURE_2D, m_texture);
  glBindVertexArray(vao);
  // Draw the sprite.
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

// Returns a vector value of the current position of the sprite.
Vector2f Player::getPosition() { return m_position; }

// Returns a vector value of the size of the sprite.
Vector2f Player::getSize() { return m_size; }
