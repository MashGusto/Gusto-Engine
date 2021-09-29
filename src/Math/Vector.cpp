#include "Math/Vector.h"

#include <math.h>
#include <iostream>

// Takes in the values to be stored.
Vector2f::Vector2f(float x, float y) : m_x(x), m_y(y) {};

// Gets the first value in the vector.
float Vector2f::getX() { return m_x; }

// Gets the second value in the vector.
float Vector2f::getY() { return m_y; }

// Sets the first value in the vector.
void Vector2f::setX(float x) { m_x = x; }

// Sets the second value in the vector.
void Vector2f::setY(float y) { m_y = y; }

float Vector2f::getLength()
{
  return (float) sqrt((m_x*m_x) + (m_y*m_y));
}

Vector2f Vector2f::operator - ()
{
  Vector2f vec(-m_x, -m_y);
  return vec;
}

Vector2f Vector2f::operator + (const Vector2f& addend)
{
  Vector2f vec(m_x + addend.m_x, m_y + addend.m_y);
  return vec;
}

Vector2f Vector2f::operator - (const Vector2f& subtrahend)
{
  Vector2f vec(m_x + -(subtrahend.m_x), m_y + -(subtrahend.m_y));
  return vec;
}

Vector2f& Vector2f::operator += (const Vector2f& addend)
{
  m_x += addend.m_x;
  m_y += addend.m_y;
  return *this;
}

// Overloads the subscript([]) operator to return the x and y values according to index.
float& Vector2f::operator [] (int index)
{
  if(index == 0)
    return m_x;
  else
    return m_y;
}
