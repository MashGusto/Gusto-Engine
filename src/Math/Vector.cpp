#include "Math/Vector.h"

Vector2f::Vector2f(float x, float y) : m_x(x), m_y(y) {};

float Vector2f::getX() { return m_x; }

float Vector2f::getY() { return m_y; }

float& Vector2f::operator[](int index)
{
  if(index == 0)
    return m_x;
  else
    return m_y;
}
