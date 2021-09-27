#include "Sprites/Object.h"

Object::Object(Vector2f pos, Vector2f size, std::string textureImagePath, float textureImageScale) : m_x(pos.getX()), m_y(pos.getY()), m_width(size.getX()), m_height(size.getY()), m_shader(FileManager::getShader("Texture/vertexShader.glsl"), FileManager::getShader("Texture/fragmentShader.glsl"))
{
  Texture texture(textureImagePath);
  m_texture = texture.getTexture();

  // Positions
  vertices[0]  = m_x,           vertices[1]  = m_y,            vertices[2]  = 0.f;
  vertices[5]  = m_x + m_width, vertices[6]  = m_y,            vertices[7]  = 0.f;
  vertices[10] = m_x + m_width, vertices[11] = m_y - m_height, vertices[12] = 0.f;
  vertices[15] = m_x,           vertices[16] = m_y - m_height, vertices[17] = 0.f;
  
  // Texture Coordinates
  vertices[3] = 0.f, vertices[4] = m_height/textureImageScale;
  vertices[8] = m_width/textureImageScale, vertices[9] = m_height/textureImageScale;
  vertices[13] = m_width/textureImageScale, vertices[14] = 0.f;
  vertices[18] = 0.f, vertices[19] = 0.f;

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

void Object::draw(GLFWwindow *window)
{
  m_shader.use();
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindTexture(GL_TEXTURE_2D, m_texture);
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

Vector2f Object::getPosition() { return Vector2f(m_x, m_y); }

Vector2f Object::getSize() { return Vector2f(m_width, m_height); }
