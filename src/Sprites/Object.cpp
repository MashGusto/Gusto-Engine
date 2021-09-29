#include "Sprites/Object.h"

// Takes in the position, size and texture of the immovable sprite, and assigns the values to their respective data members.
Object::Object(Vector2f pos, Vector2f size, std::string textureImagePath, float textureImageScale) : m_position(pos), m_size(size), m_shader(FileManager::getShader("Texture/vertexShader.glsl"), FileManager::getShader("Texture/fragmentShader.glsl"))
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
  vertices[3]  = 0.f,                                vertices[4]  = m_size.getY() / textureImageScale;
  vertices[8]  = m_size.getX() / textureImageScale,  vertices[9]  = m_size.getY() / textureImageScale;
  vertices[13] = m_size.getX() / textureImageScale,  vertices[14] = 0.f;
  vertices[18] = 0.f,                                vertices[19] = 0.f;
  
  // Generate buffers for the sprite, assign the vertex values to attributes to be used by the shader.
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &ebo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

// Draws the sprite to the window.
// To be called each game frame.
void Object::draw(GLFWwindow *window)
{
  // Use the sprite's shader as the one to use to draw it, and rebind the texture.
  m_shader.use();
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindTexture(GL_TEXTURE_2D, m_texture);
  glBindVertexArray(vao);
  // Draw the sprite.
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

// Returns a vector value of the position of the sprite
Vector2f Object::getPosition() { return m_position; }

// Returns a vector value of the size of the sprite
Vector2f Object::getSize() { return m_size; }
