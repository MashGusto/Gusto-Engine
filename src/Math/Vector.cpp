#include "Math/Vector.h"

// Takes in the values to be stored.
Vector2f::Vector2f(float x, float y) : m_x(x), m_y(y) {};

// Gets the first value in the vector.
float Vector2f::getX() { return m_x; }

// Gets the second value in the vector.
float Vector2f::getY() { return m_y; }

// Overloads the subscript([]) operator to return the x and y values according to index.
float& Vector2f::operator[](int index)
{
  if(index == 0)
    return m_x;
  else
    return m_y;
}
