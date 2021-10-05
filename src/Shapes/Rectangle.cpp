#include "Shapes/Rectangle.h"

#include "glm/gtc/type_ptr.hpp"

// Takes in the position, scale and color of the rectangle shape, and assigns the values to their respective data members.
Rectangle::Rectangle(glm::vec2 Position, glm::vec2 Scale, Color Color) : position(Position), scale(Scale), color(Color), shader(FileManager::getShader("color.glsl"))
{
  // Set the vertices of the rectangle according to its position and scale.

  // Positions
  vertices[0] = position.x, vertices[1] = position.y, vertices[2] = 0.f;
  vertices[6] = position.x + scale.x, vertices[7] = position.y, vertices[8] = 0.f;
  vertices[12] = position.x + scale.x, vertices[13] = position.y - scale.y, vertices[14] = 0.f;
  vertices[18] = position.x, vertices[19] = position.y - scale.y, vertices[20] = 0.f;

  // Colors
  vertices[3] = color.getRed(), vertices[4] = color.getGreen(), vertices[5] = color.getBlue();
  vertices[9] = color.getRed(), vertices[10] = color.getGreen(), vertices[11] = color.getBlue();
  vertices[15] = color.getRed(), vertices[16] = color.getGreen(), vertices[17] = color.getBlue();
  vertices[21] = color.getRed(), vertices[22] = color.getGreen(), vertices[23] = color.getBlue();

  // Generate buffers for the rectangle, and assign attributes to it, to be used by its shaders.
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &ebo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

// Move the rectangle according to keyboard input(WASD)
void Rectangle::checkMovement(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    position += glm::vec2(0.f, 0.001f);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    position += glm::vec2(-0.001f, 0.f);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    position += glm::vec2(0.f, -0.001f);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    position += glm::vec2(0.001f, 0.f);
}

// Draw the rectangle on to the screen, on the rectangle's current position.
// To be called each game frame.
void Rectangle::draw(GLFWwindow *window)
{
  // Takes in keyboard input, and calls the checkMovement function.
  checkMovement(window);

  // Repositions the vertices, according to current position.
  vertices[0] = position.x, vertices[1] = position.y;
  vertices[6] = position.x + scale.x, vertices[7] = position.y;
  vertices[12] = position.x + scale.x, vertices[13] = position.y - scale.y;
  vertices[18] = position.x, vertices[19] = position.y - scale.y;

  // Make the rectangle's shader the shader to use to draw it.
  shader.use();
  unsigned int transformLocation = glGetUniformLocation(shader.getID(), "transform");
  glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(Shader::projection));

  // Rebuffer the rectangle, and reassign the vertex attribute values.
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindVertexArray(vao);
  // Draw the rectangle.
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

// Returns a vector value of the current position of the rectangle.
glm::vec2 Rectangle::getPosition() { return position; }

// Returns a vector value of the scale of the rectangle.
glm::vec2 Rectangle::getScale() { return scale; }
