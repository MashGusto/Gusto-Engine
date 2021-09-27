#include "Math/Color.h"

Color::Color(float r, float g, float b) : m_r(r), m_g(g), m_b(b), m_a(1.f) {}

Color::Color(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {}

float Color::getRed() { return m_r; }

float Color::getGreen() { return m_g; }

float Color::getBlue() { return m_b; }

float Color::getAlpha() { return m_a; }

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
