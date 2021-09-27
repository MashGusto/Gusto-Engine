#pragma once

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
