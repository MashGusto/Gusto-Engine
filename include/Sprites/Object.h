#pragma once

/**
 * A graphical component, that is used to draw an immovable sprite at a given position, drawn with a given texture.
 */

#include "Components/Texture.h"
#include "Components/Shader.h"
#include "Components/FileManager.h"
#include "Math/Vector.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Object
{
  private:
    Vector2f m_position;
    Vector2f m_size;
    Shader m_shader;
    unsigned int m_texture;
    float vertices[20];
    unsigned int indices[6] = {
      3, 0, 2,
      2, 0, 1
    };
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
  
  public:
    Object(Vector2f pos, Vector2f size, std::string textureImagePath, float textureImageScale);
    Vector2f getPosition();
    Vector2f getSize();
    void move(GLFWwindow *window);
    void draw(GLFWwindow *window);
};
