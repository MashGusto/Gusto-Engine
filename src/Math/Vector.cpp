#include "Math/Vector.h"

#include <math.h>
#include <iostream>

// Takes in the values to be stored.
Vector2f::Vector2f() {}
Vector2f::Vector2f(float x, float y) : m_x(x), m_y(y) {}

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
  return (float)sqrt((m_x * m_x) + (m_y * m_y));
}

// For negating a vector; for example: -vec
Vector2f Vector2f::operator-() const
{
  Vector2f vec(-m_x, -m_y);
  return vec;
}

// For adding two vectors together; for example: vec1 + vec2
Vector2f Vector2f::operator+(const Vector2f &rhs) const
{
  Vector2f vec(m_x + rhs.m_x, m_y + rhs.m_y);
  return vec;
}

// For subtracting a vector from another vector; for example: vec1 - vec2
Vector2f Vector2f::operator-(const Vector2f &rhs) const
{
  Vector2f vec(m_x + -(rhs.m_x), m_y + -(rhs.m_y));
  return vec;
}

// For multiplying a vector by another vector; for example: vec1 * vec2
// Dot product multiplication
float Vector2f::operator*(const Vector2f &rhs) const
{
  Vector2f vec(m_x * rhs.m_x, m_y * rhs.m_y);
  return vec.m_x + vec.m_y;
}

// For dividing a vector by another vector; for example: vec1 / vec2
Vector2f Vector2f::operator/(const Vector2f &rhs) const
{
  Vector2f vec(m_x / rhs.m_x, m_y / rhs.m_y);
  return vec;
}

// For adding and assigning a vector into another; for example: vec1 += vec2
Vector2f &Vector2f::operator+=(const Vector2f &rhs)
{
  m_x += rhs.m_x;
  m_y += rhs.m_y;
  return *this;
}

// For adding a float to a vector; for example: vec1 + 1.f
Vector2f Vector2f::operator+(const float &rhs) const
{
  Vector2f vec(m_x + rhs, m_y + rhs);
  return vec;
}

// For subtracting a float from a vector; for example: vec1 - 1.f
Vector2f Vector2f::operator-(const float &rhs) const
{
  Vector2f vec(m_x - rhs, m_y - rhs);
  return vec;
}

// For multiplying a vector('s scalars) by a float; for example: vec1 * 2.f
Vector2f Vector2f::operator*(const float &rhs) const
{
  Vector2f vec(m_x * rhs, m_y * rhs);
  return vec;
}

// For dividing a vector('s scalars) by a float; for example: vec1 / 2.f;
Vector2f Vector2f::operator/(const float &rhs) const
{
  Vector2f vec(m_x / rhs, m_y / rhs);
  return vec;
}

// Overloads the subscript([]) operator to return the x and y values according to index.
float &Vector2f::operator[](int index)
{
  if (index == 0)
    return m_x;
  else
    return m_y;
}
