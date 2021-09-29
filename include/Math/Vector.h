#pragma once

/**
 * A container to hold position/size/vertex values.
 */

class Vector2f
{
  private:
    float m_x, m_y;
  public:
    Vector2f(float x, float y);
    float getX();
    float getY();
    float& operator[](int index);
};
