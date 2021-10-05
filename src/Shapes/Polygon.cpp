#include "Shapes/Polygon.h"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#define _USE_MATH_DEFINES
#include <cmath>

// Takes in the position, radius, number of vertices, and color of the polygon, and assigns those values to respective data members.
Polygon::Polygon(glm::vec2 Position, float Radius, unsigned int VertexCount, Color Color) : position(Position), radius(Radius), vertexCount(VertexCount), color(color), shader(FileManager::getShader("color.glsl"))
{
  // The center of the polygon
  vertices.push_back(position.x);
  vertices.push_back(position.y);
  vertices.push_back(0.f);
  vertices.push_back(color.getRed());
  vertices.push_back(color.getGreen());
  vertices.push_back(color.getBlue());

  for (int i = 0; i < vertexCount; i++)
  {
    // Setting the vertices according to its radius, and calculated using sin and cos.

    // position
    vertices.push_back(position.x + (radius * cosf(i * (M_PI * 2) / vertexCount)));
    vertices.push_back(position.y + (radius * sinf(i * (M_PI * 2) / vertexCount)));
    vertices.push_back(0.f);

    // color
    vertices.push_back(color.getRed());
    vertices.push_back(color.getGreen());
    vertices.push_back(color.getBlue());

    indices.push_back(i + 1);
    indices.push_back(0);
    if (i + 2 > vertexCount)
      indices.push_back(1);
    else
      indices.push_back(i + 2);
  }

  // Generate buffers for the polygon shape, and assign position and color attributes to it, to be used by the shaders.
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &ebo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), &indices[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

// Move the polygon, by the method of dragging with mouse.
void Polygon::checkMovement(GLFWwindow *window)
{
  double mouseX, mouseY;
  // Checks if the left mouse button in held down, and the mouse pointer is inside the polygon shape.
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
  {
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glfwGetCursorPos(window, &mouseX, &mouseY);
    mouseX = -1.f + 2.f * mouseX / windowWidth;
    mouseY = 1.f - 2.f * mouseY / windowHeight;
    if (mouseX < position.x + radius && mouseX > position.x - radius && mouseY < position.y + radius && mouseY > position.y - radius)
    {
      position.x = mouseX;
      position.y = mouseY;
    }
  }
}

// Draws the polygon, at its current position.
// To be called each game frame.
void Polygon::draw(GLFWwindow *window)
{
  // Takes in mouse input, and calls the checkMovement function.
  checkMovement(window);

  // Repositions the vertices, according to current position.
  vertices[0] = position.x, vertices[1] = position.y;
  for (int i = 0; i < vertexCount; i++)
  {
    vertices[(i * 6) + 6] = position.x + (radius * cosf(i * (M_PI * 2) / vertexCount));
    vertices[(i * 6) + 7] = position.y + (radius * sinf(i * (M_PI * 2) / vertexCount));
  }

  // Rebuffer the positions, and set its shader to be used to render the shape.
  shader.use();
  unsigned int transformLocation = glGetUniformLocation(shader.getID(), "transform");
  glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(Shader::projection));

  // Rebuffers the polygon, and reassigns the vertex attribute values.
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
  glBindVertexArray(vao);
  // Draws the polygon.
  glDrawElements(GL_TRIANGLES, vertexCount * 3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

// Get a vector value of the shape's current position.
glm::vec2 Polygon::getPosition() { return position; }

// Get the radius of the polygon.
float Polygon::getRadius() { return radius; }
