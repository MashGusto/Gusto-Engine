#pragma once

#include "System/Texture.h"
#include "System/Shader.h"
#include "System/FileManager.h"
#include "System/Color.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <vector>
#include <string>

class Shape
{
protected:
    Shader shader;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;

public:
    glm::vec2 position;

    static bool Selected;
    bool selected = false;

    Shape() {}

    virtual glm::vec2 getPosition();
    virtual void updateMovement() {}
    virtual void draw() {}
};

class Rectangle : public Shape
{
public:
    glm::vec2 scale;
    Color color;

    Rectangle(glm::vec2 Position, glm::vec2 Scale, Color Color);

    glm::vec2 getPosition();
    glm::vec2 getScale();
    void updateMovement();
    void draw();
};

class Polygon : public Shape
{
protected:
    unsigned int vertexCount;

    glm::vec2 mouseDist;

public:
    Color color;
    float radius;

    Polygon(glm::vec2 Position, float Radius, unsigned int VertexCount, Color Color);

    glm::vec2 getPosition();
    float getRadius();
    void updateMovement();
    void draw();
};