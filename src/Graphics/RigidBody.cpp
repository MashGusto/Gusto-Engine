#include "Components/Definitions.h"
#include "Graphics/RigidBody.h"

#include <iostream>
#include "glm/gtc/type_ptr.hpp"

// Takes in the position, scale and texture of the movable sprite, and assigns the values to their respective data members.
RigidBody::RigidBody(glm::vec2 Position, glm::vec2 Scale, RigidBodyType Type) : position(Position), scale(Scale), type(Type), shader(FileManager::getShader("texture.glsl"))
{
  // Set the positions of the vertices of the sprite according to its positions.

  // Positions
  vertices[0] = position.x, vertices[1] = position.y, vertices[2] = 0.f;
  vertices[5] = position.x + scale.x, vertices[6] = position.y, vertices[7] = 0.f;
  vertices[10] = position.x + scale.x, vertices[11] = position.y - scale.y, vertices[12] = 0.f;
  vertices[15] = position.x, vertices[16] = position.y - scale.y, vertices[17] = 0.f;

  // Texture Coordinates for body
  vertices[3] = 0.f, vertices[4] = 1.f;
  vertices[8] = 1.f, vertices[9] = 1.f;
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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

// Move the sprite according to keyboard input(WASD)
void RigidBody::updateMovement(GLFWwindow *window)
{
  if (type == RigidBodyType::DYNAMIC)
  {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && collided)
      velocity += glm::vec2(0.f, 0.75f);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      velocity -= glm::vec2(0.025f, 0.f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      velocity += glm::vec2(0.025f, 0.f);

    position += velocity * DT;

    if (velocity.x > 0.f)
    {
      if (collided)
        velocity -= glm::vec2(0.005f, 0.f);
      else
        velocity -= glm::vec2(0.001f, 0.f);
    }
    if (velocity.x < 0.f)
    {
      if (collided)
        velocity += glm::vec2(0.005f, 0.f);
      else
        velocity += glm::vec2(0.001f, 0.f);
    }
  }
  else if (type == RigidBodyType::STATIC)
    std::cout << "A static body cannot be moved." << std::endl;
}

// Draws the sprite to the window.
// To be called each game frame.
void RigidBody::draw(GLFWwindow *window)
{
  if (type == RigidBodyType::DYNAMIC)
  {
    // Takes in keyboard input, and calls the updateMovement function.
    updateMovement(window);

    // Reassigns the  vertex positions of the sprite, according to current position.
    vertices[0] = position.x, vertices[1] = position.y;
    vertices[5] = position.x + scale.x, vertices[6] = position.y;
    vertices[10] = position.x + scale.x, vertices[11] = position.y - scale.y;
    vertices[15] = position.x, vertices[16] = position.y - scale.y;

    // Rebuffer the sprite, and reassign the vertex attribute values.
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
  }

  // Make the sprite's shader the shader to use to draw it.
  shader.use();
  unsigned int transformLocation = glGetUniformLocation(shader.getID(), "transform");
  glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(Shader::projection));

  glBindTexture(GL_TEXTURE_2D, texture);
  glBindVertexArray(vao);

  // Draw the sprite.
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

// Sets the position of the sprite to given position.
void RigidBody::setPosition(glm::vec2 Position) { position = Position; }

void RigidBody::setScale(glm::vec2 Scale) { scale = Scale; }

void RigidBody::setMass(float Mass) { mass = Mass; }

void RigidBody::setTexture(std::string textureImagePath, float textureImageScale)
{
  Texture Texture(textureImagePath);
  texture = Texture.getTexture();

  // Texture Coordinates for Static body
  if (type == RigidBodyType::STATIC)
  {
    vertices[3] = 0.f, vertices[4] = scale.y / textureImageScale;
    vertices[8] = scale.x / textureImageScale, vertices[9] = scale.y / textureImageScale;
    vertices[13] = scale.x / textureImageScale, vertices[14] = 0.f;
    vertices[18] = 0.f, vertices[19] = 0.f;
  }

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
  glBindTexture(GL_TEXTURE_2D, texture);
  glBindVertexArray(vao);
}

// Returns a vector value of the current position of the sprite.
glm::vec2 RigidBody::getPosition() { return position; }

// Returns a vector value of the scale of the sprite.
glm::vec2 RigidBody::getScale() { return scale; }
