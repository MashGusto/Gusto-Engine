#include "Graphics/Shape.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include "glm/gtc/type_ptr.hpp"

bool Shape::Selected = false;

glm::vec2 Shape::getPosition() { return position; }

// Takes in the position, scale and color of the rectangle shape, and assigns the values to their respective data members.
Rectangle::Rectangle(glm::vec2 Position, glm::vec2 Scale, Color Color)
{
    position = Position, scale = Scale, color = Color, shader = FileManager::getShader("color.glsl");

    // Set the vertices of the rectangle according to its position and scale.

    // Positions
    vertices.push_back(position.x), vertices.push_back(position.y), vertices.push_back(0.f);
    vertices.push_back(color.getRed()), vertices.push_back(color.getGreen()), vertices.push_back(color.getBlue());
    vertices.push_back(position.x + scale.x), vertices.push_back(position.y), vertices.push_back(0.f);
    vertices.push_back(color.getRed()), vertices.push_back(color.getGreen()), vertices.push_back(color.getBlue());
    vertices.push_back(position.x + scale.x), vertices.push_back(position.y - scale.y), vertices.push_back(0.f);
    vertices.push_back(color.getRed()), vertices.push_back(color.getGreen()), vertices.push_back(color.getBlue());
    vertices.push_back(position.x), vertices.push_back(position.y - scale.y), vertices.push_back(0.f);
    vertices.push_back(color.getRed()), vertices.push_back(color.getGreen()), vertices.push_back(color.getBlue());

    indices = {
        3, 0, 2,
        2, 0, 1};

    // Generate buffers for the rectangle, and assign attributes to it, to be used by its shaders.
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

// Move the rectangle according to keyboard input(WASD)
void Rectangle::updateMovement(GLFWwindow *window)
{
    if (selected)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            position += glm::vec2(0.f, 0.01f);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            position -= glm::vec2(0.01f, 0.f);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            position -= glm::vec2(0.f, 0.01f);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            position += glm::vec2(0.01f, 0.f);
    }
}

// Draw the rectangle on to the screen, on the rectangle's current position.
// To be called each game frame.
void Rectangle::draw(GLFWwindow *window)
{
    // Takes in keyboard input, and calls the updateMovement function.
    updateMovement(window);

    double mouseX, mouseY;
    // Checks if the left mouse button in held down, and the mouse pointer is inside the rectangle shape.
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glfwGetCursorPos(window, &mouseX, &mouseY);
        mouseX = -2.f + 4.f * mouseX / windowWidth;
        mouseY = 2.f - 4.f * mouseY / windowHeight;
        if (mouseX < position.x + scale.x && mouseX > position.x - scale.x && mouseY < position.y + scale.y && mouseY > position.y - scale.x)
        {
            selected = true;
            Selected = true;
        }
        else
            selected = false;
    }

    // Repositions the vertices, according to current position.
    vertices[0] = position.x, vertices[1] = position.y;
    vertices[6] = position.x + scale.x, vertices[7] = position.y;
    vertices[12] = position.x + scale.x, vertices[13] = position.y - scale.y;
    vertices[18] = position.x, vertices[19] = position.y - scale.y;

    if (selected && Selected)
    {
        vertices[3] = 1.f, vertices[4] = 0.f, vertices[5] = 0.f;
        vertices[9] = 1.f, vertices[10] = 0.f, vertices[11] = 0.f;
        vertices[15] = 1.f, vertices[16] = 0.f, vertices[17] = 0.f;
        vertices[21] = 1.f, vertices[22] = 0.f, vertices[23] = 0.f;
    }
    else
    {
        vertices[3] = color.getRed(), vertices[4] = color.getGreen(), vertices[5] = color.getBlue();
        vertices[9] = color.getRed(), vertices[10] = color.getGreen(), vertices[11] = color.getBlue();
        vertices[15] = color.getRed(), vertices[16] = color.getGreen(), vertices[17] = color.getBlue();
        vertices[21] = color.getRed(), vertices[22] = color.getGreen(), vertices[23] = color.getBlue();
    }

    // Make the rectangle's shader the shader to use to draw it.
    shader.use();
    unsigned int transformLocation = glGetUniformLocation(shader.getID(), "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(Shader::projection));

    // Rebuffer the rectangle, and reassign the vertex attribute values.
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glBindVertexArray(vao);
    // Draw the rectangle.
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// Returns a vector value of the current position of the rectangle.
glm::vec2 Rectangle::getPosition() { return position; }

// Returns a vector value of the scale of the rectangle.
glm::vec2 Rectangle::getScale() { return scale; }

// Takes in the position, radius, number of vertices, and color of the polygon, and assigns those values to respective data members.
Polygon::Polygon(glm::vec2 Position, float Radius, unsigned int VertexCount, Color Colour)
{
    position = Position, radius = Radius, vertexCount = VertexCount, color = Colour, shader = FileManager::getShader("color.glsl");

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
void Polygon::updateMovement(GLFWwindow *window)
{
    if (selected)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            position += glm::vec2(0.f, 0.01f);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            position -= glm::vec2(0.01f, 0.f);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            position -= glm::vec2(0.f, 0.01f);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            position += glm::vec2(0.01f, 0.f);
    }
}

// Draws the polygon, at its current position.
// To be called each game frame.
void Polygon::draw(GLFWwindow *window)
{
    // Takes in mouse input, and calls the updateMovement function.
    updateMovement(window);

    double mouseX, mouseY;
    // Checks if the left mouse button in held down, and the mouse pointer is inside the polygon shape.
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glfwGetCursorPos(window, &mouseX, &mouseY);
        mouseX = -2.f + 4.f * mouseX / windowWidth;
        mouseY = 2.f - 4.f * mouseY / windowHeight;
        if (mouseX < position.x + radius && mouseX > position.x - radius && mouseY < position.y + radius && mouseY > position.y - radius)
        {
            selected = true;
            Selected = true;
        }
        else
            selected = false;
    }

    // Repositions the vertices, according to current position.
    vertices[0] = position.x, vertices[1] = position.y;
    for (int i = 0; i < vertexCount; i++)
    {
        vertices[(i * 6) + 6] = position.x + (radius * cosf(i * (M_PI * 2) / vertexCount));
        vertices[(i * 6) + 7] = position.y + (radius * sinf(i * (M_PI * 2) / vertexCount));
    }

    if (selected && Selected)
    {
        vertices[3] = 1.f, vertices[4] = 0.f, vertices[5] = 0.f;
        for (int i = 1; i <= vertexCount; i++)
        {
            vertices[(i * 6) + 3] = 1.f;
            vertices[(i * 6) + 4] = 0.f;
            vertices[(i * 6) + 5] = 0.f;
        }
    }
    else
    {
        vertices[3] = color.getRed(), vertices[4] = color.getGreen(), vertices[5] = color.getBlue();
        for (int i = 1; i <= vertexCount; i++)
        {
            vertices[(i * 6) + 3] = color.getRed();
            vertices[(i * 6) + 4] = color.getGreen();
            vertices[(i * 6) + 5] = color.getBlue();
        }
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
