#pragma once

/**
 * A graphical component, that is used to draw a movable sprite at a given position, drawn with a given texture.
 */

#include "Components/Texture.h"
#include "Components/Shader.h"
#include "Components/FileManager.h"
#include "Math/Vector.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Player
{
private:
  Shader m_shader;
  unsigned int m_texture;
  float vertices[20];
  unsigned int indices[6] = {
      3, 0, 2,
      2, 0, 1};
  unsigned int vbo;
  unsigned int vao;
  unsigned int ebo;

public:
  Vector2f m_position;
  Vector2f m_size;
  Vector2f m_velocity;
  Vector2f m_force;
  float m_mass;

  Player(Vector2f pos, Vector2f size, float mass, std::string textureImagePath, float textureImageScale);

  Vector2f getPosition();
  Vector2f getSize();
  void move(GLFWwindow *window);
  void draw(GLFWwindow *window);
};
