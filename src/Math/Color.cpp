#include "Math/Color.h"

// Constructor for rgb values.
Color::Color(float r, float g, float b) : m_r(r), m_g(g), m_b(b), m_a(1.f) {}

// Constructor for rgba values.
Color::Color(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {}

// Get the r value of the color.
float Color::getRed() { return m_r; }

// Get the g value of the color.
float Color::getGreen() { return m_g; }

// Get the b value of the color.
float Color::getBlue() { return m_b; }

// Get the a value of the color.
float Color::getAlpha() { return m_a; }

// Overloads the subscript([]) operator to return the color values according to index.
float& Color::operator[](int index)
{
  if(index == 1)
    return m_r;
  else if(index == 2)
    return m_g;
  else if(index == 3)
    return m_b;
  else
    return m_a;
}
